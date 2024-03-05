#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

class Particle {
public:
	sf::Vector2f pos, acc, force;
	sf::Color color;
	sf::Vector2f vel;

public:
	float mass = 10.0f;
	float radius = 10.0f;

private:
	sf::Vector2f G = { 0, 200 };
	sf::Vector2f lastPos;
	sf::Vector2f lockedPos;
	bool locked = false;

public:
	Particle(sf::Vector2f pos, sf::Color color, float mass, float radius);
	Particle(sf::Vector2f pos, sf::Color color, float mass, float radius, sf::Vector2f lockedPos);

public:
	void update(float dt);
};