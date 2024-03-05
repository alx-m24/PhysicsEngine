#include "Particle.hpp"

Particle::Particle(sf::Vector2f pos, sf::Color color, float mass, float radius)
{
	this->color = color;
	this->pos = pos;
	this->mass = mass;
	this->radius = radius;

	this->lastPos = pos;
	this->vel = { 0, 0 };
	this->acc = G;
	this->locked = false;
}

Particle::Particle(sf::Vector2f pos, sf::Color color, float mass, float radius, sf::Vector2f lockedPos)
{
	this->color = color;
	this->pos = lockedPos;
	this->mass = mass;
	this->radius = radius;

	this->lastPos = pos;
	this->vel = { 0, 0 };
	this->acc = G;
	this->lockedPos = lockedPos;
	this->locked = true;
}

void Particle::update(float dt)
{
	if (locked) {
		pos = lockedPos;
		return;
	}
	acc += (force / mass);

	const sf::Vector2f temp = pos;
	pos = 2.0f * pos - lastPos + acc * dt * dt;
	lastPos = temp;

	acc = G;
	force = { 0, 0 };
}
