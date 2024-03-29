#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Fluid.hpp"
#include "Common.hpp"
#include "Particle.hpp"
#include "Constraint.hpp"
#include "Spring.hpp"
#include "Cloth.hpp"
#include "Collision.hpp"
#include "InterMolecular.hpp"

class ParticleSystem : public sf::VertexArray {
private:
	// Radius of which the force will affect the particles
	unsigned int forceRange = 75;
	bool lastleft = false;
	Collision* collision;
	InterMolecularSystem* test;

private:
	sf::Vector2f TexSize;
	sf::Vector2f lastMousePos;
	sf::Vector2f mousePos;

public:
	sf::VertexArray fluidDisplay;
	sf::Texture text;

public:
	std::vector<Particle*> particles;
	std::vector<Constriant*> constriants;
	std::vector<Spring*> springs;
	std::vector<Fluid*> fluids;

private:
	void loadTexture();
	void displayUpdate();
	void setupConstraints();
	void force();

public:
	ParticleSystem(int particleCount);

public:
	void populate(int count);
	void update(float dt);
	void addParticle(sf::Vector2f pos, sf::Color color, float mass, float radius);
	void addConstraint(unsigned int idx1, unsigned int idx2, float length);
};