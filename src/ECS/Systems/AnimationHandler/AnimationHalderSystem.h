#pragma once
#include "ECS/Systems/System.h"
#include "ECS/Coordinator/Cordinator.h"


class AnimationHalderSystem : public System
{
public:
	 void update(Coordinator& entityManager);
};

