#pragma once
#include "../System.h"
#include "System/ECS/Coordinator/Cordinator.h"
#include "SFML/Graphics/RenderTarget.hpp"

class RenderSystem : public System
{
public:
	void update(Coordinator &entityManager);
	void render(Coordinator &entityManager, sf::RenderTarget *window);
};



