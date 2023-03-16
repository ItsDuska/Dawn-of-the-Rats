/*
#include "ComponentManager.h"

template<typename kys>
inline void ComponentManager::registerComponent()
{
	const char* typeName = typeid(kys).name();

	assert(this->_componentTypes.find(typeName) == this->_componentTypes.end() && "Miksi monta componenttia ? Eikö yks riitä : | ");

	this->_componentTypes.insert({ typeName, this->_nextComponentType });
	this->_componentArrays.insert({ typeName, std::make_shared<ComponentArray<kys>>() });

	++this->_nextComponentType;
}

template<typename kys>
inline uint8_t ComponentManager::getComponentType()
{
	const char* typeName = typeid(kys).name();
	assert(this->_componentTypes.find(typeName) != this->_componentTypes.end() && "Kukas tämäkin herra on.");

	return this->_componentTypes[typeName];
}

template<typename kys>
inline void ComponentManager::addComponent(uint32_t entity, kys component)
{
	this->getComponentArray<kys>()->insertData(entity, component);
}

template<typename kys>
void ComponentManager::removeComponent(uint32_t entity)
{
	this->getComponentArray<kys>()->removeData(entity);
}

template<typename kys>
inline kys& ComponentManager::getComponent(uint32_t entity)
{
	return this->getComponentArray<kys>()->GetData(entity);
}

template<typename kys>
inline std::shared_ptr<ComponentArray<kys>> ComponentManager::getComponentArray()
{
	const char* typeName = typeid(kys).name();
	assert(this->_componentTypes.find(typeName) != this->_componentTypes.end() && "Kukas tämäkin herra on.");

	return std::static_pointer_cast<ComponentArray<kys>>(this->_componentArrays[typeName]);
}

void ComponentManager::entityDestroyed(uint32_t entity)
{
	for (auto const& pair : _componentArrays)
	{
		auto const& component = pair.second;
		component->entityDestroyed(entity);
	}
}
*/