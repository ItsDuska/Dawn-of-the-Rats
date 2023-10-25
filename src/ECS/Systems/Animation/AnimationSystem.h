#pragma once
#include "ECS/Systems/System.h"


class AnimationSystem : public System
{
public: 
	void update(Coordinator& entityManager);
};
