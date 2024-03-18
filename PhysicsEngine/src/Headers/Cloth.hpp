#pragma once
#include <vector>
#include "Particle.hpp"
#include "Spring.hpp"
#include "Constraint.hpp"

class String {
public:
	String(std::vector<Particle*>* particles, std::vector<Constriant*>* constraints, unsigned int count, float spacing);
	String(std::vector<Particle*>* particles, std::vector<Spring*>* springs, unsigned int count, float spacing, float strength);
};

class Bridge {
public:
	Bridge(std::vector<Particle*>* particles, std::vector<Constriant*>* constraints, unsigned int count, float spacing);
};