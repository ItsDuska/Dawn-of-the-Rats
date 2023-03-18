#pragma once
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Sprite.hpp>

struct Gravity
{
	sf::Vector2f force;
};

struct RigidBody
{
	sf::Vector2f velocity;
	sf::Vector2f acceleration;
};

struct Transform
{
	sf::Vector2f position;
	sf::Vector2f scale;
	float rotation;
};

struct Image
{
	sf::Sprite sprite;
	//sf::FloatRect imageRect;
};