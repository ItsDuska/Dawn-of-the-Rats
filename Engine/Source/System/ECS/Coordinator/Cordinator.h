#pragma once
#include "../ComponentManager/ComponentManager.h"
#include "../EntityManager/EntityManager.h"
#include "../SystemManager/SystemManager.h"
#include "../Components/Components.h"	



class Coordinator
{
public:
	void init()
	{
		this->_componentManager = std::make_unique<ComponentManager>();
		this->_entityManager = std::make_unique<EntityManager>();
		this->_systemManager = std::make_unique<SystemManager>();
	}

	uint32_t createEntity()
	{
		return this->_entityManager->createEntity();
	}

	void destroyEntity(uint32_t entity)
	{
		this->_entityManager->destroyEntity(entity);
		this->_componentManager->entityDestroyed(entity);
		this->_systemManager->entityDestroyed(entity);
	}

	template<typename kys>
	void registerComponent()
	{
		this->_componentManager->registerComponent<kys>();
	}

	template<typename kys>
	void addComponent(uint32_t entity, kys component)
	{
		this->_componentManager->addComponent<kys>(entity, component);

		auto signature = this->_entityManager->getSignature(entity);
		signature.set(this->_componentManager->getComponentType<kys>(), true);
		this->_entityManager->setSignature(entity, signature);

		this->_systemManager->entitySignatureChanged(entity, signature);
	}

	template<typename kys>
	void removeComponent(uint32_t entity)
	{
		this->_componentManager->removeComponent<kys>(entity);

		auto signature = this->_entityManager->getSignature(entity);
		signature.set(this->_componentManager->getComponentType<kys>(), false);
		this->_entityManager->setSignature(entity, signature);

		this->_systemManager->entitySignatureChanged(entity, signature);
	}

	template<typename kys>
	kys& getComponent(uint32_t entity)
	{
		return this->_componentManager->getComponent<kys>(entity);
	}

	template<typename kys>
	uint8_t GetComponentType()
	{
		return this->_componentManager->getComponentType<kys>();
	}

	template<typename kys>
	std::shared_ptr<kys> RegisterSystem()
	{
		return this->_systemManager->registerSystem<kys>();
	}

	template<typename kys>
	void SetSystemSignature(Signature signature)
	{
		this->_systemManager->setSignature<kys>(signature);
	}

private:
	std::unique_ptr<ComponentManager> _componentManager;
	std::unique_ptr<EntityManager> _entityManager;
	std::unique_ptr<SystemManager> _systemManager;
};


