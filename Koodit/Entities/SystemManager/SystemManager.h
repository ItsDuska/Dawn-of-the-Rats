#pragma once
#include "../../Config/EntityComponentSystemConfig.h"
#include "../Systems/System.h"
#include <unordered_map>
#include <memory>

class SystemManager
{
public:
	template<typename kys>
	std::shared_ptr<kys> registerSystem();

	template<typename kys>
	void setSignature(Signature signature);

	void entityDestroyed(uint32_t entity);
	void entitySignatureChanged(uint32_t entity, Signature entitySignature);

private:
	std::unordered_map<const char*, Signature> _signatures{};
	std::unordered_map<const char*, std::shared_ptr<System>> _systems{};
};
