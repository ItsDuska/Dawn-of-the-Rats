#pragma once
#include "../Utils/Animation/AnimationHandler.h"
#include "../Utils/Assets/AssetManager.h"
#include <SFML/Graphics.hpp>

class Player
{
private:
	void inputs();
	sf::Sprite player;
	AnimationHandler animationHandler;
	bool facingLeft = false;
	sf::Vector2i currentAnimationFrames = {0,6};
	std::vector< sf::Vector2i> allAnimationFrames = AssetManager::getframeIndexes("Player");
public:
	Player();
	void update();
	void render(sf::RenderTarget* window);
	sf::Vector2f getPosition();
};

