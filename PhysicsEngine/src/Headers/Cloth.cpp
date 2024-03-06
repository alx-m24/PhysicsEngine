#include "Cloth.hpp"

String::String(std::vector<Particle*>* particles, std::vector<Constriant*>* constraints, unsigned int count, float spacing)
{
	sf::Vector2f pos = { 0, 0 };
	particles->push_back(new Particle(pos, sf::Color::White, 10.0f, 2.0f, {500, 100}));
	for (int i = 1; i < count; ++i) {
		pos.x += spacing;
		particles->push_back(new Particle(pos, sf::Color::White, 10.0f, 2.0f));

		constraints->push_back(new Constriant((*particles)[particles->size() - 1], (*particles)[particles->size() - 2], spacing));
	}
}
