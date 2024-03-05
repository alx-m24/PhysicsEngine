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
	float dist = Vec::getDist(p1->pos, p2->pos);
	float offSet = (length - dist) / 2.0f;

	sf::Vector2f dir = p2->pos - p1->pos;
	dir = Vec::normalize(dir);
	p1->pos -= (dir * offSet);

	dir = p1->pos - p2->pos;
	dir = Vec::normalize(dir);
	p2->pos -= (dir * offSet);

	(*this)[0].position = p1->pos;
	(*this)[1].position = p2->pos;
}
