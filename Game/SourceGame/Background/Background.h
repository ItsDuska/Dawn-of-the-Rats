#pragma once

#include "Assets/Textures/AssetManager.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Shader.hpp>
#include <filesystem>
#include <iostream>


struct BackgroundLayer {
	sf::Sprite first;
	sf::Sprite second;
};

class Background
{
public:
	Background(std::string filePath, sf::Vector2f windowSize);
	void render(sf::RenderTarget& window, sf::Shader* shader = NULL, sf::Vector2f playerPos = sf::Vector2f());
	void update(sf::Vector2f playerPosition, float velocity);
private:
	void initBackground(std::filesystem::path path, sf::Vector2f windowSize);

	sf::Vector2f windowSize;
	sf::Vector2f imageSize;
	int imageCount = 0;
	std::vector<std::unique_ptr<BackgroundLayer>> backgrounds;
};

