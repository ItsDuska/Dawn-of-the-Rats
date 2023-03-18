#include "MovingSystem.h"


void MovingSystem::update(Coordinator& entityManager)
{
	for (auto& entity : this->mEntities)
	{
		auto& rigidBody = entityManager.getComponent<component::RigidBody>(entity);
		

		this->acceleration(entityManager, rigidBody);
		this->deceleration(entityManager, rigidBody);
	}
}

void MovingSystem::acceleration(Coordinator& entityManager, component::RigidBody &rigidBody)
{
	rigidBody.velocity.x += rigidBody.acceleration * rigidBody.direction.x;

	if (rigidBody.velocity.x > 0.f && rigidBody.velocity.x > rigidBody.maxVelocity)
	{
		rigidBody.velocity.x = rigidBody.maxVelocity;
	}
	else if (rigidBody.velocity.x < 0.f && rigidBody.velocity.x < -rigidBody.maxVelocity)
	{
		rigidBody.velocity.x = -rigidBody.maxVelocity;
	}
}

void MovingSystem::deceleration(Coordinator& entityManager, component::RigidBody& rigidBody)
{
	if (rigidBody.velocity.x > 0.f)
	{
		rigidBody.velocity.x -= rigidBody.deceleration;
		if (rigidBody.velocity.x < 0.f) { rigidBody.velocity.x = 0.f; }
	}
	else if (rigidBody.velocity.x < 0.f)
	{
		rigidBody.velocity.x += rigidBody.deceleration;
		if (rigidBody.velocity.x > 0.f) { rigidBody.velocity.x = 0.f; }
	}
}
