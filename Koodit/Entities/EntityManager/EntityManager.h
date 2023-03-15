#pragma once
#include "../../Config/EntityComponentSystemConfig.h"
#include <queue>
#include <array>



class EntityManager
{
public:
	EntityManager();
	uint32_t createEntity();
	void destroyEntity(uint32_t entity);

	void setSignature(uint32_t entity, Signature signature);
	Signature getSignature(uint32_t entity);

private:
	std::queue<uint32_t> _availableEntities{};
	std::array<Signature, MAX_ENTITIES> _signatures{};
	std::uint32_t _livingEntityCount{};
};
