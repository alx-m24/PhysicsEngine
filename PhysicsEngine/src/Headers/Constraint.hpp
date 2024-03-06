#pragma once
#include <SFML/Graphics.hpp>
#include "Vec.hpp"
#include "Particle.hpp"

class Constriant : public sf::VertexArray {
private:
	Particle* p1;
	Particle* p2;

private:
	float length;

public:
	Constriant(Particle* p1, Particle* p2, float length);

public:
	void update();
};