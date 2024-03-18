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
	// Normalize so that when multiplied, the magnitude of the vector is equal to the calculated offset
	sf::Vector2f dir = Vec::normalize(p1->pos - p2->pos);

	// Total mass
	float total_mass = p1->mass + p2->mass;

	// Distance to move for the particles to match the required [constraint]length
	float offset1 = (p2->mass / total_mass) * (length - dist);
	float offset2 = (p1->mass / total_mass) * (length - dist);

	/*
	p1->pos += (dir * offset);
	p2->pos -= (dir * offset);*/

	p1->pos += (dir * offset1);
	p2->pos -= (dir * offset2);

	// This is only for the display of the line
	(*this)[0].position = p1->pos;
	(*this)[1].position = p2->pos;
}
