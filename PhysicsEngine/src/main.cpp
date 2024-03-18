/* --The best setting for this simulation is 4Hz (substeps = 4)-- */

// SFML
#include <SFML/Graphics.hpp>
// Other
#include <vector>
#include <iostream>
// My headers
#include "Headers/Common.hpp"
#include "Headers/Useful.hpp"
#include "Headers/Game.hpp"

// Global Variables
sf::RenderWindow* window;
sf::Font arial;
// Number of substeps
unsigned int substeps = 4;
float largest = -1.0f;
bool toReset = false;

int main() {
	setupWindow();

	srand(time(0));
	
	// Class containing nearly everythin
	Game game;

	while (window->isOpen()) {
		game.Input();

		game.Update();

		game.Render();
	}

	return EXIT_SUCCESS;
}