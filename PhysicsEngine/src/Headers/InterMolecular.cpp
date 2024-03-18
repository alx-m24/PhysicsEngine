#include "InterMolecular.hpp"

InterMolecularSystem::InterMolecularSystem(unsigned int count, float mass, float att, float rep, sf::Color color, std::vector<Particle*>* particles)
{
	netForce = att + (-1.0f * rep);
	netForce *= 10.0f;
	//std::cout << netForce << std::endl;

	sf::Vector2u winSize = window->getSize();
	for (int i = 0; i < count; ++i) {
		Particle* newP = new Particle(sf::Vector2f(rand() % winSize.x, rand() % winSize.y), color, mass, 10.0f);

		particles->push_back(newP);
		this->push_back(newP);
	}
}

void InterMolecularSystem::update()
{
	for (Particle* p1 : *this) {
		for (Particle* p2 : *this) {
			if (p1 == p2) continue;

			sf::Vector2f dir = Vec::normalize(p2->pos - p1->pos);
			float dist = Vec::getDist(p1->pos, p2->pos);

			p1->force += (dir * (netForce / dist));
		}
	}
}
