#pragma once
#include "../Config/EntityComponentSystemConfig.h"
#include <set>

/*
Tänne kaikki logiikka
esim collisionit,
tai movement tai fysiikat
*/
class Coordinator;

class System
{
public:
	std::set<uint32_t> mEntities;
};