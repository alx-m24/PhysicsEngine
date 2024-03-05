#include "Game.hpp"

Game::Game()
{
	clock.restart();
}

void Game::Input()
{
	sf::Event events;
	while (window->pollEvent(events)) {
		switch (events.type)
		{
		case sf::Event::Closed:
			window->close();
			break;
		default:
			break;
		}
	}
}

void Game::Update()
{
	window->clear();
	spider->update(clock.restart().asSeconds());
}

void Game::Render()
{
	spider->show();
	window->display();
}
