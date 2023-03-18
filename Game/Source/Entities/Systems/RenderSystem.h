#pragma once
#include "System/ECS/Systems/System.h"
#include "SFML/Graphics/RenderTarget.hpp"
#include "../Components/Components.h"

class RenderSystem : public System
{
public:
	void update(Coordinator &entityManager);
	void render(Coordinator &entityManager, sf::RenderTarget *window);
};



