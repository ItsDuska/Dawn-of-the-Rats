#include "CollisionSystem.h"


void CollisionSystem::update(Coordinator& entityManager, const Chunk& chunk)
{
	for (uint32_t entity : this->mEntities)
	{
		auto& collider = entityManager.getComponent<Component::Collider>(entity);
		auto& rigidbody = entityManager.getComponent<Component::RigidBody>(entity);
		auto const& transform = entityManager.getComponent<Component::Transform>(entity);

		/*
			Hassu hassu collisoion check tähän
			Oma func block ja entity collisiolle
			Block collisioniin tarvitaan ChunkMap
		*/
		collider.blockCollision = this->blockCollision(entityManager, chunk, transform);
		collider.entityCollision = this->entityCollision(entityManager);
	}
}

bool CollisionSystem::blockCollision(Coordinator& entityManager, const Chunk& chunk, const Component::Transform transform)
{
	//sf::Vector2i entityPositionInChunkMap(
		//std::floor(chunk.chunkCoord * (transform.position.x / chunk.gridSize.x) * )
	//	)

	return false;
}

bool CollisionSystem::entityCollision(Coordinator& entityManager)
{
	return false;
}