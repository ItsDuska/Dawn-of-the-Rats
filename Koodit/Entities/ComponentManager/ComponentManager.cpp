#include "ComponentManager.h"

template<typename kys>
void ComponentManager::registerComponent()
{
	const char* typeName = typeid(kys).name();

	assert(this->_componentTypes.find(typeName) == this->_componentTypes.end() && "Miksi monta componenttia ? Eikö yks riitä : | ");

	this->_componentTypes.insert({ typeName, this->_nextComponentType });
	this->_componentArrays.insert({ typeName, std::make_shared<ComponentArray<kys>>() });

	++this->_nextComponentType;
}

template<typename kys>
ComponentType ComponentManager::getComponentType()
{
	const char* typeName = typeid(kys).name();
	assert(this->_componentTypes.find(typeName) != this->_componentTypes.end() && "Kukas tämäkin herra on.");

	return mComponentTypes[typeName];
}

template<typename kys>
void ComponentManager::addComponent(Entity entity, kys component)
{
	this->getComponentArray<kys>()->insertData(entity, component);
}

template<typename kys>
void ComponentManager::removeComponent(Entity entity)
{
	this->getComponentArray<kys>()->removeData(entity);
}

template<typename kys>
kys& ComponentManager::getComponent(Entity entity)
{
	return this->getComponentArray<kys>()->GetData(entity);
}

template<typename kys>
std::shared_ptr<ComponentArray<kys>> ComponentManager::getComponentArray()
{
	const char* typeName = typeid(kys).name();
	assert(this->_componentTypes.find(typeName) != this->_componentTypes.end() && "Kukas tämäkin herra on.");

	return std::static_pointer_cast<ComponentArray<kys>>(this->_componentArrays[typeName]);
}

void ComponentManager::entityDestroyed(Entity entity)
{
	for (auto const& pair : _componentArrays)
	{
		auto const& component = pair.second;
		component->entityDestroyed(entity);
	}
}
