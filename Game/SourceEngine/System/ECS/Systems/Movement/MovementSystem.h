#pragma once

#include "System/ECS/Systems/System.h"
#include "System/ECS/Coordinator/Cordinator.h"

class MovementSystem : public System
{
public:
	void update(Coordinator& entityManager);
private:
	const float GRAVITY = 0.5;
	const float MAX_FALLING_VELOCITY = 15.0f;

	void acceleration(Component::RigidBody& rigidBody);
	void deceleration(Component::RigidBody & rigidBody);

	void gravity(Component::RigidBody& rigidBody);
};