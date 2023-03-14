#pragma once
#include "../../Config/EntityComponentSystemConfig.h"
#include <set>

/*
Tänne kaikki logiikka
esim collisionit,
tai movement tai fysiikat
*/

class System
{
public:
	std::set<Entity> mEntities;
};