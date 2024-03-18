#include "Collision.hpp"

Collision::Collision(std::vector<Particle*>* particles)
{
	this->particles = particles;

	resetGrid();
}

bool Collision::inBounds(sf::Vector2i pos) const
{
	return (pos.x >= 0 && pos.y >= 0 && pos.x <= cellNum.x && pos.y <= cellNum.y);
}

unsigned int Collision::toIdx(sf::Vector2i i) const
{
	return i.x * cellNum.y + i.y;
}

void Collision::launchThread(Particle* p1, Cell* cell)
{

	threads.push_back(new std::thread(&Collision::checkCollisionsCell, this, p1, cell));
	//threads[threads.size() - 1]->detach();
}

void Collision::resetGrid()
{
	if (cellSize != largest * 2 || toReset) {
		cellSize = largest * 2;

		cellNum = sf::Vector2i(sf::Vector2f(window->getSize()) / cellSize);

		for (Cell* c : *this) delete c;
		this->clear();

		for (int j = 0; j <= cellNum.y; ++j) {
			for (int i = 0; i <= cellNum.x; ++i) {
				this->push_back(new Cell());
			}
		}
		toReset = false;
	}/*
	if (cellSize != 33.75f) {
		cellSize = 33.75f;

		cellNum = sf::Vector2i(sf::Vector2f(window->getSize()) / cellSize);

		for (Cell* c : *this) delete c;
		this->clear();

		for (int j = 0; j <= cellNum.y; ++j) {
			for (int i = 0; i <= cellNum.x; ++i) {
				this->push_back(new Cell());
			}
		}
	}*/
	else {
		for (Cell* c : *this) c->clear();
	}

	for (int i = 0; i < particles->size(); ++i) {
		Particle* p = (*particles)[i];
		sf::Vector2i pos = sf::Vector2i(p->pos / cellSize);

		if (!inBounds(pos)) continue;

		unsigned int idx = toIdx(pos);
		(*this)[idx]->push_back(i);
	}
}

void Collision::UpdateCollision()
{
	resetGrid();

	for (int i = 0; i <= cellNum.x; ++i) {
		for (int j = 0; j <= cellNum.y; ++j) {
			Cell* c = (*this)[toIdx(sf::Vector2i(i, j))];

			if (c->size() < 1) continue;

			for (unsigned int a : *c) {
				for (int x = -1; x < 2; ++x) {
					for (int y = -1; y < 2; ++y) {
						int newI = i + x;
						int newJ = j + y;

						if (!inBounds(sf::Vector2i(newI, newJ))) continue;

						checkCollisionsCell((*particles)[a], (*this)[toIdx(sf::Vector2i(newI, newJ))]);
						//launchThread((*particles)[a], (*this)[toIdx(sf::Vector2i(newI, newJ))]);
					}
				}

				for (std::thread* thread : threads) {
					thread->join();
					delete thread;
				}
				threads.clear();
			}
		}
	}


	/*
	for (Particle* p1 : *particles) {
		for (Particle* p2 : *particles) {
			if (p1 != p2) checkCollisions(p1, p2);
		}
	}*/
}

void Collision::checkCollisionsCell(Particle* p1, Cell* cell)
{
	if (cell->size() < 1) return;

	for (unsigned int i : *cell) {
		Particle* p2 = (*particles)[i];

		if (p1 == p2) continue;

		checkCollisions(p1, p2);
	}  
}

void Collision::checkCollisions(Particle* p1, Particle* p2)
{
	float dist = Vec::getDist(p1->pos, p2->pos);
	float sR = p1->radius + p2->radius;

	if (dist < sR) {
		solveCollision(p1, p2, sR - dist);
	}
}

void Collision::solveCollision(Particle* p1, Particle* p2, float offset)
{
	// Overlap between two circles
	offset = offset / 2.0f;

	float total_mass = p1->mass + p2->mass;
	float offset1 = (p2->mass / total_mass) * offset;
	float offset2 = (p1->mass / total_mass) * offset;

	// Direction between both cirlces
	sf::Vector2f dir = Vec::normalize(p1->pos - p2->pos);

	p1->pos += (dir * offset1);
	p2->pos -= (dir * offset2);
}
