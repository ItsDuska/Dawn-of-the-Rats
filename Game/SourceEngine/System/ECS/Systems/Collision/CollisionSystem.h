#pragma once
#include "System/ECS/Systems/System.h"
#include "System/ECS/Coordinator/Cordinator.h"
#include "World/Generation/Chunks/Chunk/Chunk.h"

class CollisionSystem : public System
{
	void update(Coordinator& entityManager, const Chunk& chunk);
	bool blockCollision(Coordinator& entityManager, const Chunk& chunk, const Component::Transform transform);
	bool entityCollision(Coordinator& entityManager);
};

