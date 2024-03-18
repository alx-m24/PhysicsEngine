#include "Game.hpp"

void Game::applyBlur()
{
	displayFluid.clear();
	displayFluid.draw(particleSystem->fluidDisplay, &particleSystem->text);
	displayFluid.display();

	sf::Sprite fluids(displayFluid.getTexture());
	blur.setUniform("u_direction", sf::Vector2f(1.0, 0.0));
	displayFluid.draw(fluids, &blur);
	displayFluid.display();

	fluids = sf::Sprite(displayFluid.getTexture());
	blur.setUniform("u_direction", sf::Vector2f(0.0, 1.0));
	displayFluid.draw(fluids, &blur);
	displayFluid.display();

	fluids = sf::Sprite(displayFluid.getTexture());
	blur.setUniform("u_direction", sf::Vector2f(-1.0, 0.0));
	displayFluid.draw(fluids, &blur);
	displayFluid.display();

	fluids = sf::Sprite(displayFluid.getTexture());
	blur.setUniform("u_direction", sf::Vector2f(0.0, -1.0));
	window->draw(fluids, &blur);
}

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
	unsigned int num = 0;
	std::cout << num << std::endl;

	particleSystem = new ParticleSystem(num);

	clock.restart();

	fpsText.setFont(arial);
	fpsText.setFillColor(sf::Color::Red);
	fpsText.setCharacterSize(32);

	blur.loadFromFile("C:\\Users\\alexa\\OneDrive\\Coding\\C++\\PhysicsEngine\\PhysicsEngine\\src\\Shader\\Blur.frag", sf::Shader::Fragment);
	blur.setUniform("u_resolution", 2.0f);

	displayFluid.create(window->getSize().x, window->getSize().y);
	blur.setUniform("u_resolution", sf::Vector2f(displayFluid.getTexture().getSize()));
	blur.setUniform("strength", blurStrength);
	std::cout << blurStrength << std::endl;
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
		case sf::Event::Resized:
			window->setView(sf::View(sf::FloatRect(0, 0, events.size.width, events.size.height)));
			displayFluid.setView(window->getView());
			toReset = true;
			break;
		default:
			break;
		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
		blurStrength += 0.01f;
		blur.setUniform("strength", blurStrength);
		std::cout << blurStrength << std::endl;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
		blurStrength -= 0.01f;
		blur.setUniform("strength", blurStrength);
		std::cout << blurStrength << std::endl;
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
	applyBlur();
	for (Constriant* constraint : particleSystem->constriants) window->draw(*constraint);
	for (Spring* spring : particleSystem->springs) window->draw(*spring);
	window->draw(*particleSystem, &particleSystem->text);

	window->draw(fpsText);
	window->display();
}
