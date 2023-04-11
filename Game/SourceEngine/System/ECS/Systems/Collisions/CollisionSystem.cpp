#include "CollisionSystem.h"

void CollisionSystem::update(Coordinator& entityManager)
{
	for (uint32_t entity : this->mEntities)
	{
		auto& collider = entityManager.getComponent<Component::Collider>(entity);

		/*
			Hassu hassu collisoion check tähän
			Oma func block ja entity collisiolle
			Block collisioniin tarvitaan ChunkMap
		*/
		collider.blockCollision = this->blockCollision(entityManager);
		collider.entityCollision = this->entityCollision(entityManager);
	}
}

bool CollisionSystem::blockCollision(Coordinator& entityManager)
{
	return false;
}

bool CollisionSystem::entityCollision(Coordinator& entityManager)
{
	return false;
}
