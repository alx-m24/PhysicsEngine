#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include "Common.hpp"
#include "Particle.hpp"
#include "Constraint.hpp"
#include "Cloth.hpp"

class ParticleSystem : public sf::VertexArray {
private:
	// Radius of which the force will affect the particles
	unsigned int forceRange = 75;
	String* string;

private:
	sf::Vector2f TexSize;
	sf::Vector2f lastMousePos;
	sf::Vector2f mousePos;

public:
	sf::Texture text;

public:
	std::vector<Particle*> particles;
	std::vector<Constriant*> constriants;

private:
	void loadTexture();
	void displayUpdate();
	void setupConstraints();
	void force();

public:
	ParticleSystem();
	ParticleSystem(int particleCount);

public:
	void populate(int count);
	void update(float dt);
	void addParticle(sf::Vector2f pos, sf::Color color, float mass, float radius);
	void addConstraint(unsigned int idx1, unsigned int idx2, float length);
};