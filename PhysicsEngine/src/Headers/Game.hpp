#pragma once
#include <SFML/Graphics.hpp>
#include "Common.hpp"

class Game {
private:
	sf::Clock clock;

public:
	Game();

public:
	void Input();
	void Update();
	void Render();
};