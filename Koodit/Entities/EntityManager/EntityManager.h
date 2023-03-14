#pragma once
#include "../../Config/EntityComponentSystemConfig.h"
#include <queue>
#include <array>



class EntityManager
{
public:
	EntityManager();
	Entity createEntity();
	void destroyEntity(Entity entity);

	void setSignature(Entity entity, Signature signature);
	Signature getSignature(Entity entity);

private:
	std::queue<Entity> _availableEntities{};
	std::array<Signature, MAX_ENTITIES> _signatures{};
	std::uint32_t _livingEntityCount{};
};
