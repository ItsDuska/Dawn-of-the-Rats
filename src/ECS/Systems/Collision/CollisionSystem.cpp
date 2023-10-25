#include "CollisionSystem.h"
#include "ECS/Coordinator/Cordinator.h"
#include <cmath>

void CollisionSystem::update(Coordinator& entityManager, 
	const std::vector<std::unique_ptr<Chunk>>* chunks,const ChunkSettings& chunkSettings, const std::vector<sf::Vector2i>  &chunkCords)
{
	for (auto& entity : this->mEntities)
	{
		auto& collider = entityManager.getComponent<Component::Collider>(entity);
		auto& rigidbody = entityManager.getComponent<Component::RigidBody>(entity);
		auto& transform = entityManager.getComponent<Component::Transform>(entity);
		auto& hitbox = entityManager.getComponent<Component::Hitbox>(entity);
		auto& state = entityManager.getComponent<Component::State>(entity);

		this->colliding = false;
		state.onGround = false;

		float entityPositionInArrayX = (transform.futurePosition.x / chunkSettings.tileSize.x);
		float entityPositionInArrayY = (transform.futurePosition.y / chunkSettings.tileSize.y);

		int entityPositionInChunkX = std::floor(std::fmod(entityPositionInArrayX, chunkSettings.gridSize.x));
		int entityPositionInChunkY = std::floor(std::fmod(entityPositionInArrayY, chunkSettings.gridSize.y));

		int chunkPositionX = (std::floor((float)entityPositionInArrayY / chunkSettings.gridSize.x) + chunkSettings.RENDERDISTANCE);
		int chunkPositionY = (std::floor((float)entityPositionInArrayX / chunkSettings.gridSize.y) + chunkSettings.RENDERDISTANCE);

		if (entityPositionInChunkX < 0)
		{
			entityPositionInChunkX += chunkSettings.gridSize.x;
		}
		
		const int chunkIndex = this->getChunkIndex(chunkCords,sf::Vector2i(chunkPositionX,chunkPositionY));

		if (chunkIndex == -1)
		{
			std::cout << "\n\nEntity real position : " << transform.position.x << "x  " << transform.position.y << "y\n";
			std::cout << "\nentityPositionInChunkMap : " << entityPositionInChunkX << "x  " << entityPositionInChunkY << "y\n";
			std::cout << "\ngridSize : " << chunkSettings.gridSize.x << "x  " << chunkSettings.gridSize.y << "y\n";
			std::cout << "\ntileSize : " << chunkSettings.tileSize.x << "x  " << chunkSettings.tileSize.y << "y\n\n";
			continue;
		}
		//TODO: CHUNK INDEX ON JOSTAKIN KUMMAN SYYSTÄ -1 VÄLILLÄ
		this->blockCollision(entityManager, chunks->at(chunkIndex), transform, chunkSettings, 
			sf::Vector2i(entityPositionInChunkX,entityPositionInChunkY), hitbox, rigidbody,state.onGround);
		this->entityCollision(entityManager); // EI OLE VIELÄ OLEMASSA !!
	}
}

void CollisionSystem::blockCollision(Coordinator& entityManager, 
	const std::unique_ptr<Chunk> &chunk, Component::Transform& transform, 
	const ChunkSettings& chunkSettings,sf::Vector2i entityPositionInChunk,Component::Hitbox hitbox,
	Component::RigidBody& rigidbody, bool& onGround)
{
	if (!chunk.get()->isDrawable)
	{
		return;
	}

	if (chunk.get()->blockMap.size() == 0)
	{
		return;
	}

	this->hasCollidedHorizontaly = false;
	this->hasCollidedVerticly = false;
	
	int i = -1;

	for (sf::Vector2i neighborBlock : this->neighborBlockPositons)
	{
		if (this->hasCollidedHorizontaly && this->hasCollidedVerticly)
		{
			break;
		}

		i++;
		sf::Vector2i newBlockPosition(entityPositionInChunk.x + neighborBlock.x, entityPositionInChunk.y + neighborBlock.y);

		if (!this->inBounds(newBlockPosition, chunkSettings.gridSize))
		{
			continue;
		}

		const int newBlockPositionXTemp = newBlockPosition.x + 1;
		const int newBlockPositionYTemp = newBlockPosition.y + 1;

		if (!chunk.get()->blockMap[newBlockPositionXTemp][newBlockPositionYTemp].isBlock)
		{
			continue;
		}
		
		if (!chunk.get()->blockMap[newBlockPositionXTemp][newBlockPositionYTemp].isSolid)
		{
			continue;
		}

		sf::Vector2f blockPositionInWorld(
			(float)(((chunk.get()->chunkCoord.y - chunkSettings.RENDERDISTANCE) * chunkSettings.gridSize.x) + newBlockPosition.x) * chunkSettings.tileSize.x,
			(float)(((chunk.get()->chunkCoord.x - chunkSettings.RENDERDISTANCE) * chunkSettings.gridSize.y) + newBlockPosition.y) * chunkSettings.tileSize.y
		);

		/* REAL COLLISION LOGIC STARTS HERE: */
		
		sf::Vector2f blockHalfSize{chunkSettings.tileSize.x / 2.f, chunkSettings.tileSize.y / 2.f};
		sf::Vector2f blockCenter{blockPositionInWorld.x + blockHalfSize.x, blockPositionInWorld.y + blockHalfSize.y};

		float deltaX = transform.futurePosition.x - blockCenter.x;
		float deltaY = transform.futurePosition.y - blockCenter.y;

		float entityHalfSizeX = hitbox.size.x / 2.f;
		float entityHalfSizeY = hitbox.size.y / 2.f;

		float intersectX = std::abs(deltaX) - (entityHalfSizeX + blockHalfSize.x);
		float intersectY = std::abs(deltaY) - (entityHalfSizeY + blockHalfSize.y);

		if (!(intersectX < 0.0f && intersectY < 0.0f))
		{
			this->palikka[i].setPosition(sf::Vector2f(0, -1000));
			continue;
		}

		this->palikka[i].setPosition(blockPositionInWorld);
		this->colliding = true;

		if (intersectX > intersectY && !this->hasCollidedHorizontaly)
		{
			if (deltaX > 0.0f)
			{
				transform.futurePosition.x -= intersectX;
				rigidbody.velocity.x = 0.f;
			}
			else
			{
				transform.futurePosition.x += intersectX;
				rigidbody.velocity.x = 0.f;
			}

			this->hasCollidedHorizontaly = true;
		}
		else if (!this->hasCollidedVerticly)
		{
			if (deltaY > 0.0f)
			{
				transform.futurePosition.y -= intersectY;
				rigidbody.velocity.y = 0.f;
			}
			else
			{
				transform.futurePosition.y += intersectY;
				rigidbody.velocity.y = 0.f;
				onGround = true;
			}

			this->hasCollidedVerticly = true;
		}
	}
}

void CollisionSystem::entityCollision(Coordinator& entityManager)
{
	return;
}

void CollisionSystem::render(sf::RenderTarget* window)
{
	if (!this->colliding)
	{
		return;
	}

	for (int i = 0; i < 4; i++)
	{
		window->draw(this->palikka[i]);
	}
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
		std::cout << "ERROR: NO CHUNK_POSITION_INDEX  -> " <<position.x << "x  " << position.y << "y\n";
		return -1;
	}
}

CollisionSystem::CollisionSystem()
{
	this->colliding = false;

	for (int i = 0; i < 4; i++)
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
