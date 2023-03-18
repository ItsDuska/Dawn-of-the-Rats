#pragma once
#include "../Entities/Entity.h"
#include "../Entities/MovableEntity.h"
#include "../GUI/Inventory/Inventory.h"
#include "Assets/Animation/AnimationHandler.h"
#include "PlayerStats.h"

#include <SFML/System/Time.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

#include "../Entities/EntityCollisionHandler.h"

class Player : public Entity, MovableEntity, EntityCollisionHandler
{
private:
	sf::Clock clock;
	PlayerStats stats;
	AnimationHandler animationHandler;
	Inventory _inventory;
	bool facingLeft = false;
	const sf::Time cooldownTime = sf::seconds(0.4f);
	sf::Vector2f direction = { 0.f,0.f };
	const float SPEED = 0.5f;
	//const float acceleration = 1.8f;
	//const float maxVelocity = 9.f;
	//const float deceleration = 0.7f;
	//sf::Vector2f velocity = {0.f,0.f};
	sf::Vector2i currentAnimationFrames = {0,6};
	std::vector< sf::Vector2i> allAnimationFrames = AssetManager::getframeIndexes("Player");
	void inputs();
	//void accelerationHandler();
	//void decelerationHandler();
	

	sf::RectangleShape hitboxes;

public:
	Player();
	~Player();
	void update();
	void render(sf::RenderTarget* window);
	void renderInventory(sf::RenderTarget* window);
};

