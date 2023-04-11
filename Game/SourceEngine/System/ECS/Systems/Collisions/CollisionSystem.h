#pragma once
#include "System/ECS/Systems/System.h"
#include "System/ECS/Coordinator/Cordinator.h"

class CollisionSystem :public System
{
	void update(Coordinator& entityManager);
	bool blockCollision(Coordinator& entityManager);
	bool entityCollision(Coordinator& entityManager);
};

