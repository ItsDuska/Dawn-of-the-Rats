#pragma once
#include "System/ECS/Systems/System.h"
#include "../../Components/Components.h"
#include "SFML/System/Clock.hpp"
#include "SFML/window/Keyboard.hpp"
#include "SFML/Window/Mouse.hpp"

class PlayerInputSystem : System
{
public:
	void update(Coordinator& entityManager);
};