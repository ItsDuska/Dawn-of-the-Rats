#pragma once
#include "../Config/EntityComponentSystemConfig.h"
#include "../Systems/System.h"
#include <unordered_map>
#include <memory>

class SystemManager
{
public:
	template<typename kys>
	std::shared_ptr<kys> registerSystem()
	{
		const char* typeName = typeid(kys).name();
		std::cout << "INFO: Registering -> " << typeName << "\n";
		assert(this->_systems.find(typeName) == this->_systems.end() && "Miksi monta componenttia? Eikö yks riitä :|");

		auto system = std::make_shared<kys>();
		this->_systems.insert({ typeName, system });
		return system;
	}

	template<typename kys>
	void setSignature(Signature signature)
	{
		const char* typeName = typeid(kys).name();

		std::cout << "INFO: Setting siganture -> " << typeName << "\n";
		assert(this->_systems.find(typeName) != this->_systems.end() && "Kukas tämäkäkin systeemi on?");

		this->_signatures.insert({ typeName, signature });
	}

	void entityDestroyed(uint32_t entity)
	{
		for (auto const& pair : this->_systems)
		{
			auto const& system = pair.second;
			system->mEntities.erase(entity);
		}
	}

	void entitySignatureChanged(uint32_t entity, Signature entitySignature)
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

private:
	std::unordered_map<const char*, Signature> _signatures{};
	std::unordered_map<const char*, std::shared_ptr<System>> _systems{};
};
