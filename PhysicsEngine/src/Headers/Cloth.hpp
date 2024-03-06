#pragma once
#include <vector>
#include "Particle.hpp"
#include "Constraint.hpp"

class String {
public:
	String(std::vector<Particle*>* particles, std::vector<Constriant*>* constraints, unsigned int count, float spacing);
};