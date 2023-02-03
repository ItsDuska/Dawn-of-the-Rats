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
	sf::Vector2f direction = { 0.f,0.f };
	const float SPEED = 0.5f;
	const float acceleration = 1.8f;
	const float maxVelocity = 9.f;
	const float deceleration = 0.7f;
	sf::Vector2f velocity = {0.f,0.f};
	sf::Vector2i currentAnimationFrames = {0,6};
	std::vector< sf::Vector2i> allAnimationFrames = AssetManager::getframeIndexes("Player");
	void accelerationHandler();
	void decelerationHandler();
public:
	Player();
	~Player();
	void update();
	void render(sf::RenderTarget* window);
	sf::Vector2f getPosition();
};

