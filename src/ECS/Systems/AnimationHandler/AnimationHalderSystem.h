#pragma once
#include "ECS/Systems/System.h"

class AnimationHalderSystem : public System
{
public:
	 void update(Coordinator& entityManager);
};

