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
	this->clear();
	for (Particle* particle : particles) {
		if (particle->fromFluid) continue;

		sf::Vector2f pos = particle->pos;
		float radius = particle->radius;

		largest = (radius > largest) ? radius : largest;

		int idx = i << 2;

		(*this).append(pos + sf::Vector2f(-radius, -radius));
		(*this).append(pos + sf::Vector2f(-radius, radius));
		(*this).append(pos + sf::Vector2f(radius, radius));
		(*this).append(pos + sf::Vector2f(radius, -radius));

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

	i = 0;
	fluidDisplay.clear();
	for (Fluid* fluid : fluids) {
		for (Particle* particle : fluid->fluid) {
			sf::Vector2f pos = particle->pos;
			float radius = particle->radius;

			largest = (radius > largest) ? radius : largest;

			fluidDisplay.append(pos + sf::Vector2f(-radius, -radius));
			fluidDisplay.append(pos + sf::Vector2f(-radius, radius));
			fluidDisplay.append(pos + sf::Vector2f(radius, radius));
			fluidDisplay.append(pos + sf::Vector2f(radius, -radius));

			int idx = i << 2;

			sf::Color color = particle->color;
			fluidDisplay[idx + 0].color = color;
			fluidDisplay[idx + 1].color = color;
			fluidDisplay[idx + 2].color = color;
			fluidDisplay[idx + 3].color = color;

			fluidDisplay[idx + 0].texCoords = sf::Vector2f(0, 0);
			fluidDisplay[idx + 1].texCoords = sf::Vector2f(TexSize.x, 0);
			fluidDisplay[idx + 2].texCoords = sf::Vector2f(TexSize.x, TexSize.y);
			fluidDisplay[idx + 3].texCoords = sf::Vector2f(0, TexSize.y);

			++i;
		}
	}
}

void ParticleSystem::setupConstraints()
{
	/*
	for (int i = 0; i < 4; ++i) {
		particles.push_back(new Particle({ 100, 300 }, sf::Color::Red, 50, 11));
	}

	float length = 175.0f;
	float diagonal = sqrt((length * length) + (length * length));
	constriants.push_back(new Constriant(particles[particles.size() - 1], particles[particles.size() - 2], length));
	constriants.push_back(new Constriant(particles[particles.size() - 1], particles[particles.size() - 3], length));
	constriants.push_back(new Constriant(particles[particles.size() - 3], particles[particles.size() - 4], length));
	constriants.push_back(new Constriant(particles[particles.size() - 4], particles[particles.size() - 2], length));
	constriants.push_back(new Constriant(particles[particles.size() - 4], particles[particles.size() - 1], diagonal));
	//constriants.push_back(new Constriant(particles[particles.size() - 4], particles[particles.size() - 1], diagonal));
	*/
	
	//particles.push_back(new Particle({ 470, 300 }, sf::Color::Magenta, 2500, 30));

	/*
	float att = 500;
	float rep = 0;
	test = new InterMolecularSystem(200, 10, att, rep, sf::Color::Blue, &particles);*/
	particles.push_back(new Particle({ 500, 300 }, sf::Color::White, 20, 15, {500, 300}));
	particles.push_back(new Particle({ 500, 200 }, sf::Color::Red, 20, 15));

	springs.push_back(new Spring(particles[particles.size() - 1], particles[particles.size() - 2], 100, 500));
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

ParticleSystem::ParticleSystem(int particleCount)
{
	loadTexture();

	this->setPrimitiveType(sf::PrimitiveType::Quads);

	this->populate(particleCount);
	setupConstraints();

	collision = new Collision(&particles);

	//String(&particles, &constriants, 50, 10.0f);
	//Bridge(&particles, &constriants, 50, 10.0f);
	//String(&particles, &springs, 10, 10.0f, 150.0f);

	fluidDisplay.setPrimitiveType(sf::Quads);
	//fluids.push_back(new Fluid(1000, sf::Color::Blue, 10.0f, &particles));
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
		sf::Color::Green,
	};

	for (int i = 0; i < count; ++i) {
		Particle* newParticle = new Particle(sf::Vector2f(rand() % winSize.x, rand() % winSize.y), colors[rand() % std::size(colors)], 50.0f, 10.0f);
		particles.push_back(newParticle);

		int idx = i << 2;

		sf::Vector2f pos = newParticle->pos;
		float radius = newParticle->radius;

		largest = (radius > largest) ? radius : largest;

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

		//test->update();
		for (Fluid* fluid : fluids) fluid->update();
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

		collision->UpdateCollision();
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
