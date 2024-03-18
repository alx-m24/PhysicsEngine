#include "Fluid.hpp"

Fluid::Fluid(unsigned int count, sf::Color color, float mass, std::vector<Particle*>* particles)
{
	sf::Vector2u winSize = window->getSize();

	for (int i = 0; i < count; ++i) {
		Particle* newParticle = new Particle(sf::Vector2f(rand() % winSize.x, rand() % winSize.y), color, mass, 10.0f);
		newParticle->fromFluid = true;

		particles->push_back(newParticle);
		fluid.push_back(newParticle);
	}
}

void Fluid::update()
{
	
}
