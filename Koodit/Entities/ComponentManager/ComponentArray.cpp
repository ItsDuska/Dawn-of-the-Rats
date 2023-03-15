#include "ComponentArray.h"

template<typename kys>
void ComponentArray<kys>::insertData(uint32_t entity, kys component)
{
	assert(this->_entityToIndexMap.find(entity) == this->_entityToIndexMap.end() && "Miksi monta componenttia? Eikö yks riitä :| ");

	size_t newIndex = _size;
	this->_entityToIndexMap[entity] = newIndex;
	this->_indexToEntityMap[newIndex] = entity;
	this->_componentArray[newIndex] = component;
	++this->_size;
}

template<typename kys>
void ComponentArray<kys>::removeData(uint32_t entity)
{
	assert(this->_entityToIndexMap.find(entity) != this->_entityToIndexMap.end() && "Poistat asiaa jota ei ole olemassa senkin pälli!");
	
	size_t indexOfRemovedEntity = this->_entityToIndexMap[entity];
	size_t indexOfLastElement = this->_size - 1;
	this->_componentArray[indexOfRemovedEntity] = this->_componentArray[indexOfLastElement];

	uint32_t entityOfLastElement = this->_indexToEntityMap[indexOfLastElement];
	this->_entityToIndexMap[entityOfLastElement] = indexOfRemovedEntity;
	this->_indexToEntityMap[indexOfRemovedEntity] = entityOfLastElement;

	this->_entityToIndexMap.erase(entity);
	this->_indexToEntityMap.erase(indexOfLastElement);

	--this->_size;

}

template<typename kys>
kys ComponentArray<kys>::getData(uint32_t entity)
{
	assert(this->_entityToIndexMap.find(entity) != this->_entityToIndexMap.end() && 
		"Valitettavasti tähän componenttiin ei juuri nyt saada yhteyttä. Laita tekstiviesti äänimerkin jäälkeen. :)");

	return this->_componentArray[this->_entityToIndexMap[entity]];
}

template<typename kys>
void ComponentArray<kys>::entityDestroyed(uint32_t entity)
{
	if (this->_entityToIndexMap.find(entity) != this->_entityToIndexMap.end())
	{
		this->removeData(entity);
	}
}
