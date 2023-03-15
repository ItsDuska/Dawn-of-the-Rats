#pragma once
#include "../../Config/EntityComponentSystemConfig.h"
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
	void insertData(uint32_t entity, kys component);
	void removeData(uint32_t entity);

	kys getData(uint32_t entity);

	void entityDestroyed(uint32_t entity) override;

private:
	std::array<kys, MAX_ENTITIES> _componentArray;
	std::unordered_map<uint32_t, size_t> _entityToIndexMap;
	std::unordered_map<size_t, uint32_t> _indexToEntityMap;
	size_t _size;
};
