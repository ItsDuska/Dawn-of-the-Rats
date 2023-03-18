#include "EntityCollisionHandler.h"


bool EntityCollisionHandler::isInBounds(sf::Vector2i currentPosition, sf::Vector2i gridSize)
{
	return currentPosition.x > 0 && currentPosition.x < gridSize.x&& currentPosition.y > 0 && currentPosition.y < gridSize.y;
}


void EntityCollisionHandler::checkCollisionSides(sf::Vector2f& veclocity)
{
	if (veclocity.x != 0) // oikealle liikkuu
	{
		veclocity.x = 0.f;
	}
	if (veclocity.y > 0)
	{
		veclocity.y = 0;
		this->_onGround = true;
	}
}

void EntityCollisionHandler::blockCollisions(
	sf::FloatRect entity,  std::vector<std::vector<bool>>  &blockMap, 
	sf::Vector2f *velocity, sf::Vector2f tileSize, sf::Vector2i gridSize, sf::Vector2i chunkCoord)
{
	for (auto neighbor : this->neighborCellPositons)
	{
		const sf::Vector2i gridPosition(
			(int)(tileSize.x * chunkCoord.x * std::floor((entity.left / gridSize.x) + neighbor.x)),
			(int)(tileSize.y * chunkCoord.y * std::floor((entity.top  / gridSize.y) + neighbor.y))
		);

		if (!isInBounds(gridPosition, gridSize))
		{
			continue;
		}

		if (!blockMap[gridPosition.y][gridPosition.x])
		{
			continue;
		}

		if(!entity.intersects(sf::FloatRect(gridPosition.x,gridPosition.y,tileSize.x,tileSize.y)))
		{
			continue;
		}

		//colliding
		
		this->checkCollisionSides(*velocity);

	}
}

bool EntityCollisionHandler::spriteCollisions(sf::FloatRect *firstSprite, sf::FloatRect *secondSprite)
{
	return firstSprite->intersects(*secondSprite);
}
