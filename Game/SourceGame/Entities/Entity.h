#pragma once
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <string>
#include "Assets/Textures/AssetManager.h"

class Entity
{
/*
	Position
	ability to move oma entity t�lle? eli movable entity
	sama holla healtille ja damagelle ja hy�kk��miselle tai puhumiselle
	rendering
	
	oma class input handlaamiselle
*/

protected:
	sf::Sprite sprite;
	void setTexture(const std::string spriteName);
public:
	sf::Vector2f getPosition();
	void setPosition(sf::Vector2f newPosition);
	virtual void render(sf::RenderTarget *window) = 0;
	virtual void update() = 0;
};