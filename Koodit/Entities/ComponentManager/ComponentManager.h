#pragma once
#include "../../Config/EntityComponentSystemConfig.h"
#include "ComponentArray.h"
#include <memory>

class ComponentManager
{
public:
	template<typename kys>
	void registerComponent()
	{
		const char* typeName = typeid(kys).name();

		assert(this->_componentTypes.find(typeName) == this->_componentTypes.end() && "Miksi monta componenttia ? Eikö yks riitä : | ");

		this->_componentTypes.insert({ typeName, this->_nextComponentType });
		this->_componentArrays.insert({ typeName, std::make_shared<ComponentArray<kys>>() });

		++this->_nextComponentType;
	}


	template<typename kys>
	uint8_t getComponentType()
	{
		const char* typeName = typeid(kys).name();
		assert(this->_componentTypes.find(typeName) != this->_componentTypes.end() && "Kukas tämäkin herra on.");

		return this->_componentTypes[typeName];
	}

	template<typename kys>
	void addComponent(uint32_t entity, kys component)
	{
		this->getComponentArray<kys>()->insertData(entity, component);
	}

	template<typename kys>
	void removeComponent(uint32_t entity)
	{
		this->getComponentArray<kys>()->removeData(entity);
	}

	template<typename kys>
	kys& getComponent(uint32_t entity)
	{
		return getComponentArray<kys>()->getData(entity);
	}

	void entityDestroyed(uint32_t entity)
	{
		for (auto const& pair : _componentArrays)
		{
			auto const& component = pair.second;
			component->entityDestroyed(entity);
		}
	}

private:
	std::unordered_map<const char*, uint8_t> _componentTypes{};

	std::unordered_map<const char*, std::shared_ptr<IComponentArray>> _componentArrays{};

	uint8_t _nextComponentType{};

	template<typename kys>
	std::shared_ptr<ComponentArray<kys>> getComponentArray()
	{
		const char* typeName = typeid(kys).name();
		assert(this->_componentTypes.find(typeName) != this->_componentTypes.end() && "Kukas tämäkin herra on.");

		return std::static_pointer_cast<ComponentArray<kys>>(this->_componentArrays[typeName]);
	}
};


