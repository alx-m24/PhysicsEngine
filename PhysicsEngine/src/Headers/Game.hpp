#pragma once
#include <SFML/Graphics.hpp>
#include "Common.hpp"
#include "ParticleSystem.hpp"
#include "Constraint.hpp"

class Game {
private:
	ParticleSystem* particleSystem;
	sf::Clock clock;
	sf::Text fpsText;
	sf::Clock fpsClock;
	unsigned int frame = 0;

private:
	void updateFps();

public:
	Game();

public:
	void Input();
	void Update();
	void Render();
};