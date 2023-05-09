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

		this->colliding = false;

		sf::Vector2i entityPositionInArray(
			transform.position.x / chunkSettings.tileSize.x,
			transform.position.y / chunkSettings.tileSize.y
		);

		// pelaajan sijainti chunkin sisällä eli arrayssa
		sf::Vector2i entityPositionInChunkMap(
			(entityPositionInArray.x % chunkSettings.gridSize.x),
			(entityPositionInArray.y % chunkSettings.gridSize.y)
		);

		//jostakin syystä arvot on flipattu toiste päin
		sf::Vector2i chunkPosition(
			(entityPositionInArray.y / chunkSettings.gridSize.x) + chunkSettings.RENDERDISTANCE,
			(entityPositionInArray.x / chunkSettings.gridSize.y) + chunkSettings.RENDERDISTANCE
		);

		const int chunkIndex = this->getChunkIndex(chunkCords,chunkPosition);

		if (chunkIndex == -1)
		{
			std::cout << "\n\nEntity real position : " << transform.position.x << "x  " << transform.position.y << "y\n";
			std::cout << "\nentityPositionInChunkMap : " << entityPositionInChunkMap.x << "x  " << entityPositionInChunkMap.y << "y\n";
			std::cout << "\ngridSize : " << chunkSettings.gridSize.x << "x  " << chunkSettings.gridSize.y << "y\n";
			std::cout << "\ntileSize : " << chunkSettings.tileSize.x << "x  " << chunkSettings.tileSize.y << "y\n\n";
			return;
		}

		collider.blockCollision = this->blockCollision(entityManager, chunks->at(chunkIndex), transform, chunkSettings, entityPositionInChunkMap, hitbox);
		collider.entityCollision = this->entityCollision(entityManager);
	}
}

bool CollisionSystem::blockCollision(Coordinator& entityManager, 
	const std::unique_ptr<Chunk> &chunk, Component::Transform transform, const ChunkSettings& chunkSettings,sf::Vector2i entityPositionInChunk,Component::Hitbox hitbox)
{
	if (!chunk.get()->isDrawable)
	{
		return false;
	}

	if (chunk.get()->blockMap.size() == 0)
	{
		return false;
	}


	//std::cout << "\nplayerPosInChunk : " << entityPositionInChunk.x << "  " << entityPositionInChunk.y << "\n";
	//std::cout << "\n" << chunk.get()->blockMap[entityPositionInChunk.y][entityPositionInChunk.x].isBlock << "\n";
	int i = -1;

	for (sf::Vector2i neighborBlock : this->neighborBlockPositons)
	{
		i++;
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
			(float)(((chunk.get()->chunkCoord.y-chunkSettings.RENDERDISTANCE) * chunkSettings.gridSize.x) + newBlockPosition.x) * chunkSettings.tileSize.x,
			(float)(((chunk.get()->chunkCoord.x - chunkSettings.RENDERDISTANCE) * chunkSettings.gridSize.y) + newBlockPosition.y) * chunkSettings.tileSize.y

		);
		std::cout << "\n\narrayIndex : " << newBlockPosition.x << "x  " << newBlockPosition.y << "y\n";
		std::cout << "\n\nEntity position : " << transform.position.x << "x  " << transform.position.y << "y\n";
		std::cout << "\n\nBlock position : " << blockPositionInWorld.x << "x  " << blockPositionInWorld.y << "y\n";

		if (collide(sf::FloatRect(hitbox.pos, hitbox.size), sf::FloatRect(blockPositionInWorld,chunkSettings.tileSize)))
		{
			std::cout << "\n\nEntity position : " << transform.position.x << "x  " << transform.position.y << "y\n";
			std::cout << "\n\nBlock position : " << blockPositionInWorld.x << "x  " << blockPositionInWorld.y << "y\n";
			std::cout << "\n\narrayIndex : " << newBlockPosition.x << "x  " << newBlockPosition.y << "y\n";
			std::cout << "\nChunk index :" << chunk.get()->chunkCoord.y << "x  " << chunk.get()->chunkCoord.x << "y\n";
			this->palikka[i].setPosition(blockPositionInWorld);
			this->colliding = true;
			std::cout << "\nCOLLISION!!\n";
		}
	}

	return false;
}

bool CollisionSystem::entityCollision(Coordinator& entityManager)
{
	return false;
}

void CollisionSystem::render(sf::RenderTarget* window)
{
	if (!this->colliding)
	{
		return;
	}
	for (int i = 0; i < 8; i++)
	{
		window->draw(this->palikka[i]);
	}
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
		std::cout << "\n\nERROR: NO CHUNK_POSITION_INDEX  -> " <<position.x << "x  " << position.y << "y\n\n";
		return -1;
	}
}


CollisionSystem::CollisionSystem()
{
	for (int i = 0; i < 8; i++)
	{
		this->palikka[i].setFillColor(sf::Color(255, 0, 0, 128));
		this->palikka[i].setOutlineColor(sf::Color::White);
		this->palikka[i].setOutlineThickness(1);
		this->palikka[i].setSize(sf::Vector2f(64, 64));
	}
}

bool CollisionSystem::inBounds(sf::Vector2i pos, sf::Vector2i bounds)
{
	return pos.x >= 0 && pos.x <= bounds.x+3 && pos.y >= 0 && pos.x <= bounds.y+3;
}
