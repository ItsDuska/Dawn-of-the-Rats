#pragma once
#include "System/ECS/Coordinator/Cordinator.h"
#include "../Components/Components.h"
#include "Assets/Textures/AssetManager.h"


class Prefab
{
protected:
	virtual void initSystem(Coordinator& entityManager, System& system) = 0;
	virtual void createEntity(Coordinator& entityManager, uint32_t& entity) = 0;
	

public:
	void createPrefab(Coordinator &entityManager, System &system, uint32_t &entity)
	{
		this->initSystem(entityManager, system);
		this->createEntity(entityManager, entity);
	}
	
};