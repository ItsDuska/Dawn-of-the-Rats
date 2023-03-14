#pragma once
#include "../ComponentManager/ComponentManager.h"
#include "../EntityManager/EntityManager.h"
#include "../SystemManager/SystemManager.h"

class Coordinator
{
public:
	void init();
	Entity createEntity();
	void destroyEntity(Entity entity);

	template<typename kys>
	void registerComponent();

	template<typename kys>
	void addComponent(Entity entity, kys component);

	template<typename kys>
	void removeComponent(Entity entity);

	template<typename kys>
	kys& getComponent(Entity entity);

	template<typename kys>
	ComponentType GetComponentType();

	template<typename kys>
	std::shared_ptr<kys> RegisterSystem();

	template<typename kys>
	void SetSystemSignature(Signature signature);

private:
	std::unique_ptr<ComponentManager> _componentManager;
	std::unique_ptr<EntityManager> _entityManager;
	std::unique_ptr<SystemManager> _systemManager;
};


