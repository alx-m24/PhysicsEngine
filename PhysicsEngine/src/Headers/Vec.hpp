#pragma once
#include <SFML/Graphics.hpp>

/*Just a note: 
* This is my OWN vector class/file.
* Everything was done by me and nothing has been copy/pasted.
* I use it in nearly all of my graphical projects.
--*/

namespace Vec {
	template <typename T>
	inline float getMagnitude(sf::Vector2<T> v) {
		return std::sqrt((v.x * v.x) + (v.y * v.y));
	}

	template <typename T>
	inline float getLength(sf::Vector2<T> v) {
		return std::sqrt((v.x * v.x) + (v.y * v.y));
	}

	template <typename T>
	inline float getDist(sf::Vector2<T> v1, sf::Vector2<T> v2) {
		return std::sqrt(((v1.x - v2.x) * (v1.x - v2.x)) + ((v1.y - v2.y) * (v1.y - v2.y)));
	}

	template<class T>
	inline sf::Vector2<T> fromAngle(float Angle)
	{
		return sf::Vector2<T>(std::cos(Angle), std::sin(Angle));
	}

	template<class T>
	inline sf::Vector2<T> fromAngle(float Angle, float mag)
	{
		return sf::Vector2<T>(mag * std::cos(Angle), mag * std::sin(Angle));
	}

	template<class T>
	inline float getAngle(sf::Vector2<T> v)
	{
		return std::atan(v.y / v.x);
	}

	template<class T>
	inline sf::Vector2<T> normalize(sf::Vector2<T> v)
	{
		float mag = getMagnitude(v);
		if (mag == 0) return { 0, 0 };
		return { T(v.x / mag), T(v.y / mag) };
	}

	inline float dotProduct(sf::Vector2f a, sf::Vector2f b) {
		return (a.x * b.x) + (a.y * b.y);
	}

	inline bool inFront(sf::Vector2f origin, sf::Vector2f point, float angle) {
		sf::Vector2f diff = point - origin;
		float dP = dotProduct(fromAngle<float>(angle), diff);

		return dP > 0;
	}
}