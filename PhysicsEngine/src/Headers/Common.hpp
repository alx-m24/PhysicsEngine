#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include "Particle.hpp"

#define PI 3.14159265358979323846

// Pointer to main window
extern sf::RenderWindow* window;
extern sf::Font arial;
extern float largest;
extern unsigned int substeps;
extern bool toReset;