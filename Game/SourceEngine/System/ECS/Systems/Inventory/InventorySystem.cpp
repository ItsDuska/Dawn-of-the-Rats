#include "InventorySystem.h"

void InventorySystem::update(Coordinator& entityManager)
{
	for (auto& entity : this->mEntities)
	{
		auto& inventory = entityManager.getComponent <Component::Inventory>(entity);

	}
}
