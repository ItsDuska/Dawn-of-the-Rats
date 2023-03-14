#pragma once
#include "../../Config/EntityComponentSystemConfig.h"
#include <unordered_map>


class IComponentArray
{
public:
	virtual ~IComponentArray() = default;
	virtual void entityDestroyed(Entity entity) = 0;
};

template<typename kys>
class ComponentArray : public IComponentArray
{
public:
	void insertData(Entity entity, kys component);
	void removeData(Entity entity);

	kys getData(Entity entity);

	void entityDestroyed(Entity entity) override;

private:
	std::array<kys, MAX_ENTITIES> _componentArray;
	std::unordered_map<Entity, size_t> _entityToIndexMap;
	std::unordered_map<size_t, Entity> _indexToEntityMap;
	size_t _size;
};
