#pragma once
#include "../Config/EntityComponentSystemConfig.h"
#include <unordered_map>


class IComponentArray
{
public:
	virtual ~IComponentArray() = default;
	virtual void entityDestroyed(uint32_t entity) = 0;
};

template<typename kys>
class ComponentArray : public IComponentArray
{
public:
	void insertData(uint32_t entity, kys component)
	{
		assert(this->_entityToIndexMap.find(entity) == this->_entityToIndexMap.end() && "Miksi monta componenttia? Eikö yks riitä :| ");

		size_t newIndex = _size;
		this->_entityToIndexMap[entity] = newIndex;
		this->_indexToEntityMap[newIndex] = entity;
		this->_componentArray[newIndex] = component;
		++this->_size;
	}

	void removeData(uint32_t entity)
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

	
	kys& getData(uint32_t entity)
	{
		assert(this->_entityToIndexMap.find(entity) != this->_entityToIndexMap.end() &&
			"Valitettavasti tähän componenttiin ei juuri nyt saada yhteyttä. Laita tekstiviesti äänimerkin jäälkeen. :)");

		return this->_componentArray[this->_entityToIndexMap[entity]];
	}

	void entityDestroyed(uint32_t entity) override
	{
		if (this->_entityToIndexMap.find(entity) != this->_entityToIndexMap.end())
		{
			this->removeData(entity);
		}
	}

private:
	std::array<kys, MAX_ENTITIES> _componentArray;
	std::unordered_map<uint32_t, size_t> _entityToIndexMap;
	std::unordered_map<size_t, uint32_t> _indexToEntityMap;
	size_t _size;
};
