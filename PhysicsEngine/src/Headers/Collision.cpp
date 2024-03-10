#include "Collision.hpp"

Collision::Collision(std::vector<Particle*>* particles)
{
	this->particles = particles;
}

void Collision::checkCollisions()
{
	for (Particle* p1 : *particles) {
		for (Particle* p2 : *particles) {
			if (p1 == p2) continue;

			float dist = Vec::getDist(p1->pos, p2->pos);
			float sR = p1->radius + p2->radius;

			if (dist <= sR) {
				solveCollision(p1, p2, sR - dist);
			}
		}
	}
}

void Collision::solveCollision(Particle* p1, Particle* p2, float offset)
{
	offset = offset / 2.0f;

	sf::Vector2f dir = p1->pos - p2->pos;
	dir = Vec::normalize(dir);

	p1->pos += (dir * offset);
	p2->pos -= (dir * offset);
}
