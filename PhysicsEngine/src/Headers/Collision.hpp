#pragma once
#include <vector>
#include <thread>
#include "Common.hpp"
#include "Vec.hpp"
#include "Particle.hpp"

class Cell : public std::vector<unsigned int> {};

class Collision : public std::vector<Cell*> {
private:
	float cellSize = 1.0f;
	sf::Vector2i cellNum;

private:
	std::vector<std::thread*> threads;
	std::vector<Particle*>* particles;

public:
	Collision(std::vector<Particle*>* particles);

public:
	bool inBounds(sf::Vector2i pos) const;
	unsigned int toIdx(sf::Vector2i i) const;
	void launchThread(Particle* p1, Cell* cell);
	void resetGrid();
	void UpdateCollision();
	void checkCollisionsCell(Particle* p1, Cell* cell);
	void checkCollisions(Particle* p1, Particle* p2);
	void solveCollision(Particle* p1, Particle* p2, float offset);
};