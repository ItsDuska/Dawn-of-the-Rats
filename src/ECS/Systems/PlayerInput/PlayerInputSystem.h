#pragma once
#include "ECS/Systems/System.h"
 

class PlayerInputSystem : public System
{
public:
	void update(Coordinator& entityManager);
};