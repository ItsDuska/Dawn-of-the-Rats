#pragma once
#include "System/ECS/Systems/System.h"
#include "../../Components/Components.h"

class MovingSystem : System
{
public:
		void update(Coordinator& entityManager);
private:
	void acceleration(Coordinator& entityManager, component::RigidBody& rigidBody);
	void deceleration(Coordinator& entityManager, component::RigidBody& rigidBody);
};

