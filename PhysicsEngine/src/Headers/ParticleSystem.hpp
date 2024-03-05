#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include "Common.hpp"
#include "Particle.hpp"
#include "Constraint.hpp"

class ParticleSystem : public sf::VertexArray {
private:
	sf::Vector2f TexSize;

public:
	std::vector<Particle*> particles;
	std::vector<Constriant*> constriants;
	sf::Texture text;

private:
	void loadTexture();
	void displayUpdate();
	void setupConstraints();

public:
	ParticleSystem();
	ParticleSystem(int particleCount);

public:
	void populate(int count);
	void update(float dt);
	void addParticle(sf::Vector2f pos, sf::Color color, float mass, float radius);
	void addConstraint(unsigned int idx1, unsigned int idx2, float length);
};