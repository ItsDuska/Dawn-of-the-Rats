#include "Cordinator.h"

void Coordinator::init()
{
	this->_componentManager = std::make_unique<ComponentManager>();
	this->_entityManager = std::make_unique<EntityManager>();
	this->_systemManager = std::make_unique<SystemManager>();
}

Entity Coordinator::createEntity()
{
	return this->_entityManager->createEntity();
}

void Coordinator::destroyEntity(Entity entity)
{
	this->_entityManager->destroyEntity(entity);
	this->_componentManager->entityDestroyed(entity);
	this->_systemManager->entityDestroyed(entity);
}

template<typename kys>
void Coordinator::registerComponent()
{
	this->_componentManager->registerComponent<kys>()
}

template<typename kys>
void Coordinator::addComponent(Entity entity, kys component)
{
	this->_componentManager->addComponent<kys>(entity, component);

	auto signature = this->_entityManager->getSignature(entity);
	signature.set(this->_componentManager->getComponentType<kys>(), true);
	this->_entityManager->setSignature(entity, signature);

	this->_systemManager->entitySignatureChanged(entity, signature);
}

template<typename kys>
void Coordinator::removeComponent(Entity entity)
{
	this->_componentManager->removeComponent<kys>(entity);

	auto signature = this->_entityManager->getSignature(entity);
	signature.set(this->_componentManager->getComponentType<kys>(), false);
	this->_entityManager->setSignature(entity, signature);

	this->_systemManager->entitySignatureChanged(entity, signature);
}

template<typename kys>
kys& Coordinator::getComponent(Entity entity)
{
	return this->_componentManager->getComponent<kys>(entity);
}

template<typename kys>
ComponentType Coordinator::GetComponentType()
{
	return this->_componentManager->getComponentType<kys>();
}

template<typename kys>
std::shared_ptr<kys> Coordinator::RegisterSystem()
{
	return this->_systemManager->registerSystem<kys>();
}

template<typename kys>
void Coordinator::SetSystemSignature(Signature signature)
{
	this->_systemManager->setSignature<kys>(signature);
}
