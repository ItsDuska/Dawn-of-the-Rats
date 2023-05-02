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

void EntityCollisionHandler::blockCollisions(std::vector<std::vector<Block>>& blockMap, sf::Vector2f tileSize, sf::Vector2i gridSize, sf::Vector2i chunkCoord)
{
	for (auto neighbor : this->neighborCellPositons)
	{
		/*

		//const sf::Vector2i gridPosition(
			//std::floor(tileSize.x * chunkCoord.x * (entity.left / gridSize.x)+neighbor.x),
			//std::floor(tileSize.y * chunkCoord.y * (entity.top / gridSize.y) + neighbor.y)
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
		*/
	}
}

bool EntityCollisionHandler::spriteCollisions(sf::FloatRect *firstSprite, sf::FloatRect *secondSprite)
{
	return firstSprite->intersects(*secondSprite);
}
