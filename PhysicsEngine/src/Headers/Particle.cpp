#include "Particle.hpp"

void Particle::limits(sf::Vector2u winSize)
{
	// Y limits
	float limit = winSize.y - this->radius;
	if (pos.y > limit) pos.y = limit;
	else {
		limit = this->radius;
		if (pos.y < limit) pos.y = limit;
	}

	// x limits
	limit = winSize.x - this->radius;
	if (pos.x > limit) pos.x = limit;
	else {
		limit = this->radius;
		if (pos.x < limit) pos.x = limit;
	}
}

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

void Particle::update(float dt, sf::Vector2u winSize)
{
	// If particle is locked
	if (locked) {
		// Set its poisiton (just to be sure)
		pos = lockedPos;
		// Exit to ignore the rest of the function
		return;
	}

	// Collision with borders
	limits(winSize);

	// F = ma
	// a = F/m
	acc += (force / mass);

	// Verlet's Integration
	const sf::Vector2f temp = pos;
	pos = 2.0f * pos - lastPos + acc * dt * dt;
	lastPos = temp;

	// Initialising the force to gravity
	acc = G;
	force = { 0, 0 };
}

bool Particle::contains(sf::Vector2f point)
{
	float dist = Vec::getDist(point, this->pos);
	return (dist <= this->radius);
}

float Particle::getEnergy(float winSizeY)
{
	if (locked) return 0.0f;

	sf::Vector2f vel = pos - lastPos;
	float speed = Vec::getMagnitude(vel);

	// K.E = (1/2) * mass * speed^2
	float KE = 0.5f * mass * (speed * speed);

	float g = Vec::getMagnitude(G);
	float height = winSizeY - pos.y;

	// G.P.E = mass * gravity * height
	float GPE = mass * g * height;

	return KE + GPE;
}
