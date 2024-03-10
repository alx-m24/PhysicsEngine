#include "ParticleSystem.hpp"

void ParticleSystem::loadTexture()
{
	this->text.loadFromFile(".\\res\\circle.png");
	this->text.setSmooth(true);
	this->text.generateMipmap();
	this->TexSize = sf::Vector2f(text.getSize());
}

void ParticleSystem::displayUpdate()
{
	int i = 0;
	this->resize(particles.size() * 4);
	for (Particle* particle : particles) {

		sf::Vector2f pos = particle->pos;
		float radius = particle->radius;

		int idx = i << 2;

		(*this)[idx + 0].position = pos + sf::Vector2f(-radius, -radius);
		(*this)[idx + 1].position = pos + sf::Vector2f(-radius, radius);
		(*this)[idx + 2].position = pos + sf::Vector2f(radius, radius);
		(*this)[idx + 3].position = pos + sf::Vector2f(radius, -radius);

		sf::Color color = particle->color;
		(*this)[idx + 0].color = color;
		(*this)[idx + 1].color = color;
		(*this)[idx + 2].color = color;
		(*this)[idx + 3].color = color;

		(*this)[idx + 0].texCoords = sf::Vector2f(0, 0);
		(*this)[idx + 1].texCoords = sf::Vector2f(TexSize.x, 0);
		(*this)[idx + 2].texCoords = sf::Vector2f(TexSize.x, TexSize.y);
		(*this)[idx + 3].texCoords = sf::Vector2f(0, TexSize.y);

		++i;
	}
}

void ParticleSystem::setupConstraints()
{
	/*
	// I know it is horrible to repeat myself (in code), but it was just for the demonstration

	//particles.push_back(new Particle({ 500, 100 }, sf::Color::White, 10, 10, {500, 100})); // Locked particle
	particles.push_back(new Particle({ 500, 100 }, sf::Color::White, 10, 10)); // Same as above but unlocked
	particles.push_back(new Particle({ 600, 150 }, sf::Color::White, 10, 10));
	particles.push_back(new Particle({ 700, 150 }, sf::Color::White, 10, 10));
	particles.push_back(new Particle({ 800, 150 }, sf::Color::White, 10, 10));

	springs.push_back(new Spring(particles[particles.size() - 1], particles[particles.size() - 2], 150));
	//constriants.push_back(new Constriant(particles[particles.size() - 2], particles[particles.size() - 3], 150));
	springs.push_back(new Spring(particles[particles.size() - 3], particles[particles.size() - 4], 50));*/
	/*
	particles.push_back(new Particle({ 470, 150 }, sf::Color::White, 10, 10, { 470, 150 }));
	particles.push_back(new Particle({ 490, 150 }, sf::Color::White, 10, 10, { 490, 150 }));
	particles.push_back(new Particle({ 510, 150 }, sf::Color::White, 10, 10, { 510, 150 }));
	particles.push_back(new Particle({ 530, 150 }, sf::Color::White, 10, 10, { 530, 150 }));

	particles.push_back(new Particle({ 470, 300 }, sf::Color::White, 10, 10));
	particles.push_back(new Particle({ 490, 300 }, sf::Color::White, 10, 10));
	particles.push_back(new Particle({ 510, 300 }, sf::Color::White, 10, 10));
	particles.push_back(new Particle({ 530, 300 }, sf::Color::White, 10, 10));

	constriants.push_back(new Constriant(particles[0], particles[4], 300));
	constriants.push_back(new Constriant(particles[1], particles[5], 300));
	constriants.push_back(new Constriant(particles[2], particles[6], 300));
	constriants.push_back(new Constriant(particles[3], particles[7], 300));
	constriants.push_back(new Constriant(particles[6], particles[5], 50));*/
	particles.push_back(new Particle({ 470, 300 }, sf::Color::Magenta, 100, 30));
}

void ParticleSystem::force()
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
		sf::Vector2f diff = mousePos - lastMousePos;

		for (Particle* particle : particles) {
			if (Vec::getDist(particle->pos, mousePos) > forceRange) continue;

			particle->force += (diff * 6000.0f);
		}
	}
}

ParticleSystem::ParticleSystem()
{
	loadTexture();
	
	this->setPrimitiveType(sf::PrimitiveType::Quads);

	int count = particles.size();
	this->resize(count * 4);

	collision = new Collision(&particles);

	setupConstraints();
}

ParticleSystem::ParticleSystem(int particleCount)
{
	loadTexture();

	this->setPrimitiveType(sf::PrimitiveType::Quads);

	this->populate(particleCount);
	setupConstraints();

	collision = new Collision(&particles);

	string = new String(&particles, &constriants, 50, 10.0f);
	//string = new String(&particles, &springs, 2, 10.0f, 150.0f);
}

void ParticleSystem::populate(int count)
{
	this->resize(count * 4);

	sf::Vector2i winSize = sf::Vector2i(window->getSize());

	sf::Color colors[] = { 
		sf::Color::Red,
		sf::Color::Blue,
		sf::Color::White,
		sf::Color::Yellow,
		sf::Color::Green
	};

	for (int i = 0; i < count; ++i) {
		Particle* newParticle = new Particle(sf::Vector2f(rand() % winSize.x, rand() % winSize.y), colors[rand() % std::size(colors)], 10.0f, 10.0f);
		particles.push_back(newParticle);

		int idx = i << 2;

		sf::Vector2f pos = newParticle->pos;
		float radius = newParticle->radius;

		(*this)[idx + 0].position = pos + sf::Vector2f(-radius, -radius);
		(*this)[idx + 1].position = pos + sf::Vector2f(-radius, radius);
		(*this)[idx + 2].position = pos + sf::Vector2f(radius, radius);
		(*this)[idx + 3].position = pos + sf::Vector2f(radius, -radius);

		sf::Color color = newParticle->color;
		(*this)[idx + 0].color = color;
		(*this)[idx + 1].color = color;
		(*this)[idx + 2].color = color;
		(*this)[idx + 3].color = color;

		(*this)[idx + 0].texCoords = sf::Vector2f(0, 0);
		(*this)[idx + 1].texCoords = sf::Vector2f(TexSize.x, 0);
		(*this)[idx + 2].texCoords = sf::Vector2f(TexSize.x, TexSize.y);
		(*this)[idx + 3].texCoords = sf::Vector2f(0, TexSize.y);
	}
}

void ParticleSystem::update(float dt)
{
	float sub_dt = dt / substeps;

	sf::Vector2u winSize = window->getSize();
	mousePos = sf::Vector2f(sf::Mouse::getPosition(*window));
	bool left = sf::Mouse::isButtonPressed(sf::Mouse::Left);

	for (int i = 0; i < substeps; ++i) {
		force();
		for (Particle* particle : particles) {
			particle->update(sub_dt, winSize);

			if (left && !lastleft) {
				if (particle->contains(mousePos)) {
					particle->isMoving = true;
				}
			}
			else if (!left && lastleft) particle->isMoving = false;

			if (particle->isMoving) particle->pos = mousePos;
		}
		for (Constriant* constraint : constriants) constraint->update();
		for (Spring* spring : springs) spring->update();
		collision->checkCollisions();
	}
	lastMousePos = mousePos;
	lastleft = left;

	displayUpdate();
}

void ParticleSystem::addParticle(sf::Vector2f pos, sf::Color color, float mass, float radius)
{
	particles.push_back(new Particle(pos, color, mass, radius));
}

void ParticleSystem::addConstraint(unsigned int idx1, unsigned int idx2, float length)
{
	constriants.push_back(new Constriant(particles[idx1], particles[idx2], length));
}
