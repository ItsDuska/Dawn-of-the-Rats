#pragma once

#include "System/ECS/Systems/System.h"
#include "System/ECS/Coordinator/Cordinator.h"

class MovementSystem : public System
{
public:
	void update(Coordinator& entityManager);
private:
	void acceleration(Coordinator& entityManager, Component::RigidBody& rigidBody);
	void deceleration(Coordinator & entityManager, Component::RigidBody & rigidBody);
};