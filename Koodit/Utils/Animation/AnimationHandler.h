#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

class AnimationHandler
{
private:
	sf::Sprite* objectsSprite;
	std::vector<sf::Texture> textures;
	sf::Vector2f scalingSize;
	unsigned int lastFrame = 0;
	float currentFrame = 0;
	float maxFrames;
	float delay;
	void addTexture(std::string path, std::vector<std::string>fileNames);
public:
	AnimationHandler(std::vector<std::string> fileNames, std::string path, float delay, sf::Sprite *sprite, sf::Vector2f scalingSize);
	void update();
};

