#include "EntityManager.h"


EntityManager::EntityManager()
{
	for (Entity entity = 0; entity < MAX_ENTITIES; ++entity)
	{
		this->_availableEntities.push(entity);
	}
}

Entity EntityManager::createEntity()
{
	assert(this->_livingEntityCount < MAX_ENTITIES && "Too many entities in existance.");

	Entity id = this->_availableEntities.front();
	this->_availableEntities.pop();

	++this->_livingEntityCount;

	return id;
}

void EntityManager::destroyEntity(Entity entity)
{
	assert(entity < MAX_ENTITIES && "Entity hyppäs laidan yli (out of range)");

	this->_signatures[entity].reset();
	this->_availableEntities.push(entity);

	--this->_livingEntityCount;
}

void EntityManager::setSignature(Entity entity, Signature signature)
{
	assert(entity < MAX_ENTITIES && "Entity hyppäs laidan yli (out of range)");

	this->_signatures[entity] = signature;
}

Signature EntityManager::getSignature(Entity entity)
{
	assert(entity < MAX_ENTITIES && "Entity hyppäs laidan yli (out of range)");

	return this->_signatures[entity];
}
