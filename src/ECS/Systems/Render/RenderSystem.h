#pragma once
#include "ECS/Systems/System.h"
#include "ECS/Coordinator/Cordinator.h"
#include "SFML/Graphics/RenderTarget.hpp"
#include <SFML/Graphics/Shader.hpp>

class RenderSystem : public System
{
public:
	void update(Coordinator &entityManager);
	void render(Coordinator &entityManager, sf::RenderTarget *window, sf::Shader* shader = NULL, sf::Vector2f playerPos = sf::Vector2f());
};



