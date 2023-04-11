#pragma once

#include "System/ECS/Systems/System.h"
#include "System/ECS/Coordinator/Cordinator.h"

#include "SFML/System/Clock.hpp"
#include "SFML/window/Keyboard.hpp"
#include "SFML/Window/Mouse.hpp"
 

class PlayerInputSystem : public System
{
public:
	void update(Coordinator& entityManager);
};