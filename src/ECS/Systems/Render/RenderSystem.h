#pragma once
#include "ECS/Systems/System.h"
#include "SFML/Graphics/RenderTarget.hpp"
#include <SFML/Graphics/Shader.hpp>
#include <SFML/System/Vector2.hpp>

class RenderSystem : public System
{
public:
	void update(Coordinator &entityManager);
	void render(Coordinator &entityManager, sf::RenderTarget *window, sf::Shader* shader = NULL, sf::Vector2f playerPos = sf::Vector2f());
};



