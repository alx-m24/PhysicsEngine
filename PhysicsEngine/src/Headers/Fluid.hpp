#pragma once
#include "Common.hpp"
#include "Particle.hpp"

class Fluid {
public:
	std::vector<Particle*> fluid;

public:
	Fluid(unsigned int count, sf::Color color, float mass, std::vector<Particle*>* particles);

public:
	void update();
};