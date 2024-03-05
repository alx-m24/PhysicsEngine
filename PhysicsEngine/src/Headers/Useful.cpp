#include "Useful.hpp"
#include "Common.hpp"

void setupWindow()
{
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;

	window = new sf::RenderWindow(sf::VideoMode(1000, 600), "Physics Engine", sf::Style::Close, settings);
	window->setVerticalSyncEnabled(true);
	window->setPosition(window->getPosition() - sf::Vector2i(0, 60));
	arial.loadFromFile("C:\\Windows\\Fonts\\arial.ttf");
}
