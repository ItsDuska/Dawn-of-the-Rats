#pragma once

#include "System/ECS/Systems/System.h"
#include "System/ECS/Coordinator/Cordinator.h"


class AnimationSystem : public System
{
public: 
	void update(Coordinator& entityManager);
};
