#pragma once
#include <vector>
#include "Particle.hpp"
#include "Common.hpp"
#include "Vec.hpp"

class InterMolecularSystem : private std::vector<Particle*> {
private:
	float netForce;

public:
	InterMolecularSystem(unsigned int count, float mass, float att, float rep, sf::Color color, std::vector<Particle*>* particles);

public:
	void update();
};