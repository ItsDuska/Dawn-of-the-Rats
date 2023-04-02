#include "MovableEntity.h"

void MovableEntity::accelerationHandler(sf::Vector2f direction)
{
	this->velocity.x += this->ACCELERATION * direction.x;

	if (this->velocity.x > 0.f && this->velocity.x > this->maxVelocity)
	{
		this->velocity.x = this->maxVelocity;
	}
	else if (this->velocity.x < 0.f && this->velocity.x < -this->maxVelocity)
	{
		this->velocity.x = -this->maxVelocity;
	}
}

void MovableEntity::decelerationHandler()
{
	if (this->velocity.x > 0.f)
	{
		this->velocity.x -= this->DECELERATION;
		if (this->velocity.x < 0.f) { this->velocity.x = 0.f; }
	}
	else if (this->velocity.x < 0.f)
	{
		this->velocity.x += this->DECELERATION;
		if (this->velocity.x > 0.f) { this->velocity.x = 0.f; }
	}
}

void MovableEntity::moveEntity(sf::Sprite* sprite)
{
	sprite->move(this->velocity);
}
