#include "EntityCollisionHandler.h"

bool EntityCollisionHandler::spriteCollisions(sf::FloatRect *firstSprite, sf::FloatRect *secondSprite)
{
	return firstSprite->intersects(*secondSprite);
}
