#include "Cordinator.h"

void Coordinator::init()
{
	this->_componentManager = std::make_unique<ComponentManager>();
	this->_entityManager = std::make_unique<EntityManager>();
	this->_systemManager = std::make_unique<SystemManager>();
}

uint32_t Coordinator::createEntity()
{
	return this->_entityManager->createEntity();
}

void Coordinator::destroyEntity(uint32_t entity)
{
	this->_entityManager->destroyEntity(entity);
	this->_componentManager->entityDestroyed(entity);
	this->_systemManager->entityDestroyed(entity);
}

template<typename kys>
inline void Coordinator::registerComponent()
{
	this->_componentManager->registerComponent<kys>();
}

template<typename kys>
inline void Coordinator::addComponent(uint32_t entity, kys component)
{
	this->_componentManager->addComponent<kys>(entity, component);

	auto signature = this->_entityManager->getSignature(entity);
	signature.set(this->_componentManager->getComponentType<kys>(), true);
	this->_entityManager->setSignature(entity, signature);

	this->_systemManager->entitySignatureChanged(entity, signature);
}

template<typename kys>
inline void Coordinator::removeComponent(uint32_t entity)
{
	this->_componentManager->removeComponent<kys>(entity);

	auto signature = this->_entityManager->getSignature(entity);
	signature.set(this->_componentManager->getComponentType<kys>(), false);
	this->_entityManager->setSignature(entity, signature);

	this->_systemManager->entitySignatureChanged(entity, signature);
}

template<typename kys>
inline kys& Coordinator::getComponent(uint32_t entity)
{
	return this->_componentManager->getComponent<kys>(entity);
}

template<typename kys>
inline uint8_t Coordinator::GetComponentType()
{
	return this->_componentManager->getComponentType<kys>();
}

template<typename kys>
inline std::shared_ptr<kys> Coordinator::RegisterSystem()
{
	return this->_systemManager->registerSystem<kys>();
}

template<typename kys>
inline void Coordinator::SetSystemSignature(Signature signature)
{
	this->_systemManager->setSignature<kys>(signature);
}
