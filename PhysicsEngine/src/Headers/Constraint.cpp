#include "Constraint.hpp"

Constriant::Constriant(Particle* p1, Particle* p2, float length)
{
	this->p1 = p1;
	this->p2 = p2;
	this->length = length;

	this->setPrimitiveType(sf::Lines);
	this->resize(2);
}

void Constriant::update()
{
	// Distance between particles
	float dist = Vec::getDist(p1->pos, p2->pos);
	// Distance to move for the particles to match the required [constraint]length
	float offset = (length - dist) / 2.0f;

	// Moving each particles HALF of the required "offset"
	sf::Vector2f dir = p1->pos - p2->pos;
	dir = Vec::normalize(dir); // Normalize so that when multiplied, the magnitude of the vector is equal to the calculated offset

	p1->pos += (dir * offset);
	p2->pos -= (dir * offset);


	// This is only for the display of the line
	(*this)[0].position = p1->pos;
	(*this)[1].position = p2->pos;
}
