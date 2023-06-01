#include "MovementSystem.h"

void MovementSystem::update(Coordinator& entityManager)
{
	for (auto& entity : this->mEntities)
	{
		auto& rigidBody = entityManager.getComponent<Component::RigidBody>(entity);
		auto& transform = entityManager.getComponent<Component::Transform>(entity);


		this->acceleration(entityManager, rigidBody);
		this->deceleration(entityManager, rigidBody);

		transform.futurePosition = transform.position + rigidBody.velocity;

		if (!transform.onGround)
		{
			transform.futurePosition.y += GRAVITY;
		}
		
	}

}


// TO DO

// Tee jumping homma loppuun ja laita collisionit y akselille



void MovementSystem::acceleration(Coordinator& entityManager, Component::RigidBody& rigidBody)
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

void MovementSystem::deceleration(Coordinator& entityManager, Component::RigidBody& rigidBody)
{
	if (rigidBody.velocity.x > 0.f)
	{
		rigidBody.velocity.x -= rigidBody.deceleration;

		if (rigidBody.velocity.x < 0.f) 
		{
			rigidBody.velocity.x = 0.f;
		}
	}
	else if (rigidBody.velocity.x < 0.f)
	{
		rigidBody.velocity.x += rigidBody.deceleration;

		if (rigidBody.velocity.x > 0.f) 
		{ 
			rigidBody.velocity.x = 0.f; 
		}
	}
}
