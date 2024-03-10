#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Vec.hpp"

class Particle {
public:
	sf::Vector2f pos, acc, force;
	sf::Color color;
	sf::Vector2f vel;

public:
	bool isMoving = false;
	float mass = 10.0f;
	float radius = 10.0f;

private:
	sf::Vector2f G = { 0, 200 };
	sf::Vector2f lastPos;
	sf::Vector2f lockedPos;
	bool locked = false;

private:
	void limits(sf::Vector2u winSize);

public:
	Particle(sf::Vector2f pos, sf::Color color, float mass, float radius);
	Particle(sf::Vector2f pos, sf::Color color, float mass, float radius, sf::Vector2f lockedPos);

public:
	void update(float dt, sf::Vector2u winSize);
	bool contains(sf::Vector2f point);
	float getEnergy(float winSizeY);
};