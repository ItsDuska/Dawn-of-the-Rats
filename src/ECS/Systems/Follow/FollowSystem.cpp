#include "FollowSystem.h"

void FollowSystem::update(Coordinator& entityManager, float dt)
{
	for (auto& entity : this->mEntities)
	{
		auto& followObject = entityManager.getComponent <Component::FollowObject>(entity);
		auto& transform = entityManager.getComponent <Component::Transform>(entity);
		const uint32_t playerId = entityManager.findEntity(followObject.name);
		const auto& parentTransform = entityManager.getComponent<Component::Hitbox>(playerId);
		const auto& parentState = entityManager.getComponent <Component::State>(playerId);

		if (isClose(transform.position, parentTransform.pos, followObject.distanceToObject) && !followObject.stopFollowing)
		{
			followObject.sinTime += dt * followObject.moveSpeed;
			followObject.sinTime = clamp(followObject.sinTime, PI, 0.f);

			float t = evaluate(followObject.sinTime);
			
			transform.futurePosition.x = lerp(transform.position.x, parentTransform.pos.x, t);
			transform.futurePosition.y = lerp(transform.position.y, parentTransform.pos.y - followObject.distanceToObject, t);
		}
		else if (!followObject.stopFollowing)
		{
			followObject.clock.restart();
			followObject.sinTime = 0;
			followObject.stopFollowing = true;
		}
		
		if (parentState.currentState != Component::EntityStates::IDLE)
		{
			followObject.stopFollowing = false;
		}
		else
		{
			transform.futurePosition.y += floating(followObject.clock.getElapsedTime().asSeconds());
		}
	}
}

float FollowSystem::evaluate(float x)
{
	return 0.5f * std::sin(x - PI / 2.f) + 0.5f;
}

float FollowSystem::clamp(float x, float upper, float lower)
{
	return std::min(upper,std::max(x,lower));
}

float FollowSystem::lerp(float a, float b, float f)
{
	return a + f * (b - a);
}
float FollowSystem::floating(float x)
{
	return std::sin(x - PI / 2.f);
}
				//pos 2 == parent
bool FollowSystem::isClose(sf::Vector2f pos, sf::Vector2f pos2, float offset)
{
	return (int)pos.x != (int)pos2.x || (int)pos.y != (int)(pos2.y - offset);
}
