#include "SystemManager.h"


template<typename kys>
std::shared_ptr<kys> SystemManager::registerSystem()
{
	const char* typeName = typeid(kys).name();

	assert(this->_systems.find(typeName) == this->_systems.end() && "Miksi monta componenttia? Eikö yks riitä :|");

	auto system = std::make_shared<T>();
	this->_systems.insert({ typeName, system });
	return system;
}

template<typename kys>
void SystemManager::setSignature(Signature signature)
{
	const char* typeName = typeid(T).name();

	assert(this->_systems.find(typeName) != this->_systems.end() && "Kukas tämäkäkin systeemi on?");

	this->_signatures.insert({ typeName, signature });
}


void SystemManager::entityDestroyed(Entity entity)
{
	for (auto const& pair : this->_systems)
	{
		auto const& system = pair.second;
		system->mEntities.erase(entity);
	}
}

void SystemManager::entitySignatureChanged(Entity entity, Signature entitySignature)
{
	for (auto const& pair : this->_systems)
	{
		auto const& type = pair.first;
		auto const& system = pair.second;
		auto const& systemSignature = this->_signatures[type];

		if ((entitySignature & systemSignature) == systemSignature)
		{
			system->mEntities.insert(entity);
		}
		else
		{
			system->mEntities.erase(entity);
		}
	}
}
