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
		auto& state = entityManager.getComponent<Component::State>(entity);

		this->colliding = false;

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
		}
		
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
			(float)(((chunk.get()->chunkCoord.y-chunkSettings.RENDERDISTANCE) * chunkSettings.gridSize.x) + newBlockPosition.x) * chunkSettings.tileSize.x,
			(float)(((chunk.get()->chunkCoord.x - chunkSettings.RENDERDISTANCE) * chunkSettings.gridSize.y) + newBlockPosition.y) * chunkSettings.tileSize.y
		);

		if (!collide(sf::FloatRect((hitbox.pos+rigidbody.velocity), hitbox.size), sf::FloatRect(blockPositionInWorld,chunkSettings.tileSize)))
		{
			this->palikka[i].setPosition(sf::Vector2f(0, -1000));
			continue;
		}
		
		this->palikka[i].setPosition(blockPositionInWorld);
		this->colliding = true;

		

		if (this->verticalCollision(transform, rigidbody, blockPositionInWorld, chunkSettings.tileSize, hitbox, onGround))
		{
			continue;
		}

		this->horizontalCollision(transform, rigidbody, blockPositionInWorld, chunkSettings.tileSize, hitbox);
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

void CollisionSystem::horizontalCollision(Component::Transform& transform, Component::RigidBody& rigidBody, sf::Vector2f collisionPosition, sf::Vector2f tileSize, const Component::Hitbox& hitbox)
{
	if (this->hasCollidedHorizontaly)
	{
		return;
	}

	if (rigidBody.direction.x < 0)
	{
		transform.futurePosition.x += rigidBody.velocity.x;
		rigidBody.velocity.x = 0;
		this->hasCollidedHorizontaly = true;
	}
	else if (rigidBody.direction.x > 0)
	{
		transform.futurePosition.x -= rigidBody.velocity.x;
		rigidBody.velocity.x = 0;
		this->hasCollidedHorizontaly = true;
	}
}

bool CollisionSystem::verticalCollision(Component::Transform& transform, Component::RigidBody& rigidBody, 
	sf::Vector2f collisionPosition, sf::Vector2f tileSize, const Component::Hitbox& hitbox, bool& onGround)
{
	if (this->hasCollidedVerticly)
	{
		return false;
	}

	if (rigidBody.velocity.y < 0) // ylös
	{
		transform.futurePosition.y += transform.futurePosition.y - collisionPosition.y;
		rigidBody.velocity.y = 0;
		this->hasCollidedVerticly = true;
		return true;

	}
	else if (rigidBody.velocity.y > 0) // alas
	{
		transform.futurePosition.y -= (transform.futurePosition.y - (collisionPosition.y - tileSize.y));
		rigidBody.velocity.y = 0;
		this->hasCollidedVerticly = true;
		onGround = true;
		return true;
	}

	return false;
}

CollisionSystem::CollisionSystem()
{
	this->colliding = false;

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
