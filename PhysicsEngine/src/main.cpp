#pragma once
// SFML
#include <SFML/Graphics.hpp>
// Other
#include <vector>
#include <iostream>
// My headers
#include "Headers/Common.hpp"
#include "Headers/Useful.hpp"
#include "Headers/Game.hpp"

sf::RenderWindow* window;
sf::Font arial;
unsigned int substeps = 4;

int main() {
	setupWindow();

	srand(time(0));

	Game game;

	while (window->isOpen()) {
		game.Input();

		game.Update();

		game.Render();
	}

	return EXIT_SUCCESS;
}