#include "MovementSystem.h"

void MovementSystem::update(Coordinator& entityManager)
{
	for (auto& entity : this->mEntities)
	{
		auto& rigidBody = entityManager.getComponent<Component::RigidBody>(entity);
		auto& transform = entityManager.getComponent<Component::Transform>(entity);
		


		this->acceleration(rigidBody);
		this->deceleration(rigidBody);
		this->gravity(rigidBody, transform.onGround);
		
		
		transform.futurePosition = transform.position + rigidBody.velocity;
		
	}

}


// TO DO

// Tee jumping homma loppuun ja laita collisionit y akselille



void MovementSystem::acceleration(Component::RigidBody& rigidBody)
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

void MovementSystem::deceleration(Component::RigidBody& rigidBody)
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

void MovementSystem::gravity(Component::RigidBody& rigidBody, const bool onGround)
{
	rigidBody.velocity.y += rigidBody.direction.y;
	//rigidBody.velocity.y = rigidBody.direction.y;
	if (rigidBody.velocity.y >= MAX_FALLING_VELOCITY)
	{
		rigidBody.velocity.y = MAX_FALLING_VELOCITY;
	}
	//if (!onGround)
	//{
	rigidBody.velocity.y += this->GRAVITY;
	//}
	
	


}

