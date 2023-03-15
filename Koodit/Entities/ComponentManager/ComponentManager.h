#pragma once
#include "../../Config/EntityComponentSystemConfig.h"
#include "ComponentArray.h"
#include <memory>

class ComponentManager
{
public:
	template<typename kys>
	void registerComponent();


	template<typename kys>
	uint8_t getComponentType();

	template<typename kys>
	void addComponent(uint32_t entity, kys component);

	template<typename kys>
	void removeComponent(uint32_t entity);

	template<typename kys>
	kys& getComponent(uint32_t entity);

	void entityDestroyed(uint32_t entity);

private:
	std::unordered_map<const char*, uint8_t> _componentTypes{};

	std::unordered_map<const char*, std::shared_ptr<IComponentArray>> _componentArrays{};

	uint8_t _nextComponentType{};

	template<typename kys>
	std::shared_ptr<ComponentArray<kys>> getComponentArray();
};


