#include "EntityManager.h"


EntityManager::EntityManager()
{
	for (uint32_t entity = 0; entity < MAX_ENTITIES; ++entity)
	{
		this->_availableEntities.push(entity);
	}
}

uint32_t EntityManager::createEntity()
{
	assert(this->_livingEntityCount < MAX_ENTITIES && "Too many entities in existance.");

	uint32_t id = this->_availableEntities.front();
	this->_availableEntities.pop();

	++this->_livingEntityCount;

	return id;
}

void EntityManager::destroyEntity(uint32_t entity)
{
	assert(entity < MAX_ENTITIES && "Entity hyppäs laidan yli (out of range)");

	this->_signatures[entity].reset();
	this->_availableEntities.push(entity);

	--this->_livingEntityCount;
}

void EntityManager::setSignature(uint32_t entity, Signature signature)
{
	assert(entity < MAX_ENTITIES && "Entity hyppäs laidan yli (out of range)");

	this->_signatures[entity] = signature;
}

Signature EntityManager::getSignature(uint32_t entity)
{
	assert(entity < MAX_ENTITIES && "Entity hyppäs laidan yli (out of range)");

	return this->_signatures[entity];
}
