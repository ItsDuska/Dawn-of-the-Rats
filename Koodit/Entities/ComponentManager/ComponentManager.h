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
	ComponentType getComponentType();

	template<typename kys>
	void addComponent(Entity entity, kys component);

	template<typename kys>
	void removeComponent(Entity entity);

	template<typename kys>
	kys& getComponent(Entity entity);

	void entityDestroyed(Entity entity);

private:
	std::unordered_map<const char*, ComponentType> _componentTypes{};

	std::unordered_map<const char*, std::shared_ptr<IComponentArray>> _componentArrays{};

	ComponentType _nextComponentType{};

	template<typename kys>
	std::shared_ptr<ComponentArray<kys>> getComponentArray();
};


