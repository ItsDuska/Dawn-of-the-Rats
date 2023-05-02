#include "CollisionSystem.h"


void CollisionSystem::update(Coordinator& entityManager, 
	const std::vector<std::unique_ptr<Chunk>>* chunks,const ChunkSettings& chunkSettings, const std::vector<sf::Vector2i>  &chunkCords)
{
	for (auto& entity : this->mEntities)
	{
		auto& collider = entityManager.getComponent<Component::Collider>(entity);
		auto& rigidbody = entityManager.getComponent<Component::RigidBody>(entity);
		auto& transform = entityManager.getComponent<Component::Transform>(entity);
		auto const& hitbox = entityManager.getComponent<Component::Hitbox>(entity);
		/*
			Hassu hassu collisoion check tähän
			Oma func block ja entity collisiolle
			Block collisioniin tarvitaan ChunkMap
		*/
	
		sf::Vector2f entityPositionInArray(
			transform.position.x / chunkSettings.tileSize.x,
			transform.position.y / chunkSettings.tileSize.y
		);

		sf::Vector2f floatEntityPositionInChunkMap(
			std::fmod(entityPositionInArray.x,chunkSettings.gridSize.x),
			std::fmod(entityPositionInArray.y, chunkSettings.gridSize.y)
		);

		sf::Vector2i entityPositionInChunkMap((int)floatEntityPositionInChunkMap.x,(int) floatEntityPositionInChunkMap.y);


		int chunkPositionX = 0;
		int chunkPositionY = 0;

		if(floatEntityPositionInChunkMap.x != 0)
		{
			chunkPositionX = (floatEntityPositionInChunkMap.x / chunkSettings.gridSize.x) + 1;
		}

		if (floatEntityPositionInChunkMap.y != 0)
		{
			chunkPositionX = (floatEntityPositionInChunkMap.y / chunkSettings.gridSize.y) + 1;
		}
		
		const int chunkIndex = this->getChunkIndex(chunkCords,sf::Vector2i(chunkPositionX,chunkPositionY));

		collider.blockCollision = this->blockCollision(entityManager, chunks->at(chunkIndex), transform, chunkSettings, entityPositionInChunkMap, hitbox.hitbox);
		collider.entityCollision = this->entityCollision(entityManager);
	}
}

bool CollisionSystem::blockCollision(Coordinator& entityManager, 
	const std::unique_ptr<Chunk> &chunk, Component::Transform transform, const ChunkSettings& chunkSettings,sf::Vector2i entityPositionInChunk,sf::Vector2f hitbox)
{
	if (!chunk.get()->isDrawable)
	{
		return false;
	}
	//std::cout << "\nChunk pos : " << chunk.get()->chunkCoord.x << "  " << chunk.get()->chunkCoord.y << "\n";


	for (sf::Vector2i neighborBlock : this->neighborBlockPositons)
	{
		sf::Vector2i newBlockPosition(entityPositionInChunk.x + neighborBlock.x, entityPositionInChunk.y + neighborBlock.y);

		if (!this->inBounds(newBlockPosition, chunkSettings.gridSize))
		{
			continue;
		}

		if (!chunk.get()->blockMap[newBlockPosition.x][newBlockPosition.y].isBlock)
		{
			continue;
		}

		if (!chunk.get()->blockMap[newBlockPosition.x][newBlockPosition.y].isSolid)
		{
			continue;
		}

		// On olemassa palikka
		sf::Vector2f blockPositionInWorld(
			(float)((chunk.get()->chunkCoord.x * chunkSettings.gridSize.x) + newBlockPosition.x) * chunkSettings.tileSize.x,
			(float)((chunk.get()->chunkCoord.y * chunkSettings.gridSize.y) + newBlockPosition.y) * chunkSettings.tileSize.y

		);

				
		if (collide(sf::FloatRect(transform.position, hitbox), sf::FloatRect(blockPositionInWorld,chunkSettings.tileSize)))
		{
			std::cout << "\nCOLLISION!!\n";
		}
	}

	return false;
}

bool CollisionSystem::entityCollision(Coordinator& entityManager)
{
	return false;
}

bool CollisionSystem::collide(sf::FloatRect entity, sf::FloatRect block)
{
	return entity.left < block.left + block.width &&
		entity.left + entity.width > block.left &&
		entity.top < block.top + block.height &&
		entity.height + entity.top > block.top;
}

int CollisionSystem::getChunkIndex(std::vector<sf::Vector2i> list, sf::Vector2i position)
{
	std::vector<sf::Vector2i>::iterator iteratorThing;
	iteratorThing = std::find(list.begin(), list.end(), position);

	if (iteratorThing != list.end())
	{   //löyty 
		return (int)(iteratorThing - list.begin());
	}
	else
	{ // ei löytynyt
		std::cout << "\n\nERROR: NO CHUNK_POSITION_INDEX\n\n";
		return 0;
	}
}


bool CollisionSystem::inBounds(sf::Vector2i pos, sf::Vector2i bounds)
{
	return pos.x >= 0 && pos.x <= bounds.x-1 && pos.y >= 0 && pos.x <= bounds.y-1;
}
