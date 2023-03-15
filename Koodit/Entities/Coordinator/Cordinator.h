#pragma once
#include "../ComponentManager/ComponentManager.h"
#include "../EntityManager/EntityManager.h"
#include "../SystemManager/SystemManager.h"
#include "../Components/Components.h"	



class Coordinator
{
public:
	void init();
	uint32_t createEntity();
	void destroyEntity(uint32_t entity);

	template<typename kys>
	void registerComponent();

	template<typename kys>
	void addComponent(uint32_t entity, kys component);

	template<typename kys>
	void removeComponent(uint32_t entity);

	template<typename kys>
	kys& getComponent(uint32_t entity);

	template<typename kys>
	uint8_t GetComponentType();

	template<typename kys>
	std::shared_ptr<kys> RegisterSystem();

	template<typename kys>
	void SetSystemSignature(Signature signature);

private:
	std::unique_ptr<ComponentManager> _componentManager;
	std::unique_ptr<EntityManager> _entityManager;
	std::unique_ptr<SystemManager> _systemManager;
};


