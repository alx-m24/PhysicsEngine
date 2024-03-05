#include "ParticleSystem.hpp"

void ParticleSystem::loadTexture()
{
	this->text.loadFromFile("C:\\Users\\alexa\\OneDrive\\Coding\\C++\\PhysicsEngine\\PhysicsEngine\\res\\circle.png");
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
	particles.push_back(new Particle(sf::Vector2f(rand() % window->getSize().x, rand() % window->getSize().y), sf::Color::Magenta, 10.0f, 10.0f, sf::Vector2f(window->getSize().x / 2.0f, 100)));
	particles.push_back(new Particle(sf::Vector2f(rand() % window->getSize().x, rand() % window->getSize().y), sf::Color::Yellow, 10.0f, 10.0f));
	particles.push_back(new Particle(sf::Vector2f(rand() % window->getSize().x, rand() % window->getSize().y), sf::Color::Red, 10.0f, 10.0f));
	particles.push_back(new Particle(sf::Vector2f(rand() % window->getSize().x, rand() % window->getSize().y), sf::Color::Blue, 10.0f, 10.0f));
	
	constriants.push_back(new Constriant(particles[0], particles[1], 75.0f));
	constriants.push_back(new Constriant(particles[0], particles[2], 75.0f));
	constriants.push_back(new Constriant(particles[2], particles[3], 75.0f));
	constriants.push_back(new Constriant(particles[3], particles[4], 75.0f));
}

ParticleSystem::ParticleSystem()
{
	loadTexture();
	
	this->setPrimitiveType(sf::PrimitiveType::Quads);

	int count = particles.size();
	this->resize(count * 4);

	setupConstraints();
}

ParticleSystem::ParticleSystem(int particleCount)
{
	loadTexture();

	this->setPrimitiveType(sf::PrimitiveType::Quads);

	this->populate(particleCount);
	setupConstraints();
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

	for (int i = 0; i < substeps; ++i) {
		for (Particle* particle : particles) {
			particle->update(sub_dt);
		}
		for (Constriant* constraint : constriants) constraint->update();
	}

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
