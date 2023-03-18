#pragma once
#include "../Config/EntityComponentSystemConfig.h"
#include "System/ECS/Coordinator/Cordinator.h"
#include <set>

/*
T�nne kaikki logiikka
esim collisionit,
tai movement tai fysiikat
*/

class System
{
public:
	std::set<uint32_t> mEntities;
};