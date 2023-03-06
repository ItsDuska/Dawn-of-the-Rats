#include "Entity.h"

void Entity::setTexture(std::string spriteName)
{
	this->sprite.setTexture(AssetManager::getTexture(spriteName));
}


sf::Vector2f Entity::getPosition()
{
	return this->sprite.getPosition();
}

void Entity::setPosition(sf::Vector2f newPosition)
{
	this->sprite.setPosition(newPosition);
}


