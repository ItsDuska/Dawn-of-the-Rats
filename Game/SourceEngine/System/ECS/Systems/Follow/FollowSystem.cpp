#include "FollowSystem.h"

void FollowSystem::update(Coordinator& entityManager, float dt)
{
	for (auto& entity : this->mEntities)
	{
		auto& followObject = entityManager.getComponent <Component::FollowObject>(entity);
		auto& transform = entityManager.getComponent <Component::Transform>(entity);
		const auto& state = entityManager.getComponent <Component::State>(entity);
		//std::cout << entityManager.findEntity(followObject.name);
		const auto& parentTransform = entityManager.getComponent<Component::Hitbox>(entityManager.findEntity(followObject.name));

		

		if (isClose(transform.position, parentTransform.pos, followObject.distanceToObject))
		{
			followObject.sinTime += dt * followObject.moveSpeed;
			followObject.sinTime = clamp(followObject.sinTime,PI, 0.f);
			float t = evaluate(followObject.sinTime);
			
			transform.futurePosition.x = lerp(transform.position.x, parentTransform.pos.x, t);
			transform.futurePosition.y = lerp(transform.position.y, parentTransform.pos.y-followObject.distanceToObject, t);
			
			//std::cout << t;
		}
		else
		{
			//std::cout << transform.futurePosition.x << " " << transform.futurePosition.y << "\n";
			//std::cout << parentTransform.pos.x << " " << parentTransform.pos.y << "\n";
			followObject.sinTime = 0;
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
				//pos 2 == parent
bool FollowSystem::isClose(sf::Vector2f pos, sf::Vector2f pos2, float offset)
{
	return (int)pos.x != (int)pos2.x || (int)pos.y != (int)(pos2.y - offset);
	//return pos.x < pos2.x + std::abs(2) || pos.y != pos2.y; 
}
