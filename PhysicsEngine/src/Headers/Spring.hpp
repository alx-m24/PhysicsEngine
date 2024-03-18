#pragma once
#include <SFML/Graphics.hpp>
#include "Particle.hpp"

class Spring : public sf::VertexArray {
private:
	Particle* p1;
	Particle* p2;

private:
	sf::Vector2f displacement;

private:
	float length;
	float strength;

public:
	Spring(Particle* p1, Particle* p2, float length, float strength);

public:
	void update();
};