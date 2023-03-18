#pragma once
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Sprite.hpp>

class MovableEntity
{
protected:
	sf::Vector2f velocity = {0.f,0.f};
	float maxVelocity = 9.f;
	const float ACCELERATION = 1.8f;
	const float DECELERATION = 0.7f;

	void accelerationHandler(const sf::Vector2f direction);
	void decelerationHandler();
	void moveEntity(sf::Sprite* sprite);
};