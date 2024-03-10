#pragma once
#include <vector>
#include "Vec.hpp"
#include "Particle.hpp"

class Collision {
private:
	std::vector<Particle*>* particles;

public:
	Collision(std::vector<Particle*>* particles);

public:
	void checkCollisions();
	void solveCollision(Particle* p1, Particle* p2, float offset);
};