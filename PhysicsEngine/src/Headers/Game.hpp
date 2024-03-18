#pragma once
#include <SFML/Graphics.hpp>
#include "Common.hpp"
#include "ParticleSystem.hpp"
#include "Constraint.hpp"

class Game {
private:
	ParticleSystem* particleSystem;

private:
	sf::Clock clock;
	sf::Shader blur;
	sf::RenderTexture displayFluid;
	float blurStrength = 2.8f;

private:
	sf::Text fpsText;
	sf::Clock fpsClock;
	unsigned int frame = 0;

private:
	void applyBlur();
	void updateFps();

public:
	Game();

public:
	void Input();
	void Update();
	void Render();
};