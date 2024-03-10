#include "Spring.hpp"

Spring::Spring(Particle* p1, Particle* p2, float strength)
{
	this->setPrimitiveType(sf::Lines);
	this->resize(2);

	(*this)[0].color = sf::Color::Blue;
	(*this)[1].color = sf::Color::Blue;

	this->p1 = p1;
	this->p2 = p2;
	this->length = length;
	this->strength = strength;

	this->displacement = p1->pos - p2->pos;
}

void Spring::update()
{
	// Hooke's law
	sf::Vector2f force = -this->strength * displacement;

	p1->force += force;
	p2->force -= force;

	this->displacement = p1->pos - p2->pos;

	(*this)[0].position = p1->pos;
	(*this)[1].position = p2->pos;
}
