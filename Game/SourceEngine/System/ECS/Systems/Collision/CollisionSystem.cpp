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

		//sf::Vector2i entityPositionInArray(std::floor(transform.position.x / chunkSettings.tileSize.x),std::floor(transform.position.y / chunkSettings.tileSize.y));
		float entityPositionInArrayX = (transform.futurePosition.x / chunkSettings.tileSize.x);
		float entityPositionInArrayY = (transform.futurePosition.y / chunkSettings.tileSize.y);


		// pelaajan sijainti chunkin sisällä eli arrayssa
		//sf::Vector2i entityPositionInChunkMap(
			//(entityPositionInArrayX % chunkSettings.gridSize.x),
			//(entityPositionInArrayY % chunkSettings.gridSize.y)
		//);
		int entityPositionInChunkX = std::floor(std::fmod(entityPositionInArrayX, chunkSettings.gridSize.x));
		int entityPositionInChunkY = std::floor(std::fmod(entityPositionInArrayY, chunkSettings.gridSize.y));

		//jostakin syystä arvot on flipattu toiste päin
		//sf::Vector2i chunkPosition(
		//	(entityPositionInArray.y / chunkSettings.gridSize.x + chunkSettings.RENDERDISTANCE),
		//	(entityPositionInArray.x / chunkSettings.gridSize.y + chunkSettings.RENDERDISTANCE)
		//	);

		int chunkPositionX = (std::floor((float)entityPositionInArrayY / chunkSettings.gridSize.x) + chunkSettings.RENDERDISTANCE);
		int chunkPositionY = (std::floor((float)entityPositionInArrayX / chunkSettings.gridSize.y) + chunkSettings.RENDERDISTANCE);


		//std::cout << entityPositionInArrayX;
		//std::cout << "\n" << std::floor((float)entityPositionInArrayX / chunkSettings.gridSize.x+1) << "\n";

		if (entityPositionInChunkX < 0)
		{
			entityPositionInChunkX += chunkSettings.gridSize.x;
		}

		//std::cout << "\nchunkPos : " << chunkPositionY << "x  " << chunkPositionX << "y\n";


		/*
		
		FOR FUTURE OLLI:


		collisionit röpöttää koska chunkkia vaihtaessa chunk arrayn järjestyst muuttuu

		esim jos menee vasemmalle eli negatiiviselle:
		oikea mitä pitäisi tapahtua
		chunk (1,1)  ->  (0,1)
		
		
		*/



		//int chunkIndex = chunkPositionY + chunkPositionX * ((chunkSettings.RENDERDISTANCE * 2) + 1);

		
		const int chunkIndex = this->getChunkIndex(chunkCords,sf::Vector2i(chunkPositionX,chunkPositionY));

		if (chunkIndex == -1)
		{
			std::cout << "\n\nEntity real position : " << transform.position.x << "x  " << transform.position.y << "y\n";
			std::cout << "\nentityPositionInChunkMap : " << entityPositionInChunkX << "x  " << entityPositionInChunkY << "y\n";
			std::cout << "\ngridSize : " << chunkSettings.gridSize.x << "x  " << chunkSettings.gridSize.y << "y\n";
			std::cout << "\ntileSize : " << chunkSettings.tileSize.x << "x  " << chunkSettings.tileSize.y << "y\n\n";
			
		}

		/*
		if (chunkIndex < 0)
		{
			std::cout << "AMOGUS";
			chunkIndex += chunks->size();
			entityPositionInChunkMap.x += chunkSettings.gridSize.x;
		}
		*/


		//std::cout << chunkIndex << "Chunk index\n";
		
		this->blockCollision(entityManager, chunks->at(chunkIndex), transform, chunkSettings, sf::Vector2i(entityPositionInChunkX,entityPositionInChunkY), hitbox, rigidbody);
		this->entityCollision(entityManager);
	}
}

void CollisionSystem::blockCollision(Coordinator& entityManager, 
	const std::unique_ptr<Chunk> &chunk, Component::Transform& transform, 
	const ChunkSettings& chunkSettings,sf::Vector2i entityPositionInChunk,Component::Hitbox hitbox,
	Component::RigidBody& rigidbody)
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
	
	//std::cout << "\nchunk : " << chunk.get()->chunkCoord.y << "x  " << chunk.get()->chunkCoord.x << "y\n";
	//std::cout << "\nplayerPosInChunk : " << entityPositionInChunk.y << "  " << entityPositionInChunk.x << "\n";
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

		if (!chunk.get()->blockMap[newBlockPosition.x+1][newBlockPosition.y].isBlock)
		{
			continue;
		}
		
		if (!chunk.get()->blockMap[newBlockPosition.x+1][newBlockPosition.y].isSolid)
		{
			continue;
		}

		// On olemassa palikka
		sf::Vector2f blockPositionInWorld(
			(float)(((chunk.get()->chunkCoord.y-chunkSettings.RENDERDISTANCE) * chunkSettings.gridSize.x) + newBlockPosition.x) * chunkSettings.tileSize.x,
			(float)(((chunk.get()->chunkCoord.x - chunkSettings.RENDERDISTANCE) * chunkSettings.gridSize.y) + newBlockPosition.y) * chunkSettings.tileSize.y

		);

		if (!collide(sf::FloatRect(hitbox.pos, hitbox.size), sf::FloatRect(blockPositionInWorld,chunkSettings.tileSize)))
		{
			this->palikka[i].setPosition(sf::Vector2f(0, -1000));
			continue;
		}
		
		// collided

		this->palikka[i].setPosition(blockPositionInWorld);
		this->colliding = true;

		this->horizontalCollision(transform, rigidbody, blockPositionInWorld, chunkSettings.tileSize);
		

		//std::cout << "\nCOLLISION!!\n";
		//transform.futurePosition = transform.position;
		//transform.position.x += -rigidbody.velocity.x;
	}

	return;
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

void CollisionSystem::horizontalCollision(Component::Transform& transform, Component::RigidBody& rigidBody, sf::Vector2f collisionPosition, sf::Vector2f tileSize)
{
	if (this->hasCollidedHorizontaly)
	{
		return;
	}

	if (rigidBody.direction.x < 0)
	{
		transform.futurePosition.x = transform.position.x + 2;
		rigidBody.velocity.x = 0;
		this->hasCollidedHorizontaly = true;

	}
	else if (rigidBody.direction.x > 0)
	{
		transform.futurePosition.x = transform.position.x-2;
		rigidBody.velocity.x = 0;
		this->hasCollidedHorizontaly = true;
	}

}

void CollisionSystem::verticalCollision(Component::Transform& transform, Component::RigidBody& rigidBody, sf::Vector2f collisionPosition, sf::Vector2f tileSize)
{
	if (this->hasCollidedVerticly)
	{
		return;
	}

	if (rigidBody.direction.y < 0) // ylös
	{
		transform.futurePosition.y = transform.position.y + 2;
		rigidBody.velocity.y = 0;
		this->hasCollidedVerticly = true;

	}
	else if (rigidBody.direction.y > 0) // alas
	{
		transform.futurePosition.y = transform.position.y - 2;
		rigidBody.velocity.y = 0;
		this->hasCollidedVerticly = true;
	}
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
