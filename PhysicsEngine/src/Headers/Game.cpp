#include "Game.hpp"

void Game::updateFps()
{
	if (fpsClock.getElapsedTime().asSeconds() >= 1.0f) {
		fpsText.setString("FPS: " + std::to_string(frame));
		frame = 0;
		fpsClock.restart();
	}
	++frame;
}

Game::Game()
{
	particleSystem = new ParticleSystem(10);
	clock.restart();

	fpsText.setFont(arial);
	fpsText.setFillColor(sf::Color::Red);
	fpsText.setCharacterSize(32);
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

	particleSystem->update(clock.restart().asSeconds());

	updateFps();
}

void Game::Render()
{
	for (Constriant* constraint : particleSystem->constriants) window->draw(*constraint);
	for (Spring* spring : particleSystem->springs) window->draw(*spring);
	window->draw(*particleSystem, &particleSystem->text);
	window->draw(fpsText);

	window->display();
}
