#pragma once
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Clock.hpp>

namespace Component
{ 

	struct Gravity
	{
		sf::Vector2f force;
	};

	struct RigidBody
	{
		float maxVelocity;
		float acceleration;
		float deceleration;
		sf::Vector2f velocity;
		sf::Vector2f direction;
	};

	struct Transform
	{
		sf::Vector2f futurePosition;
		sf::Vector2f position;
		bool facingLeft;
		//sf::Vector2f scale;
		//float rotation;
	};

	struct Image
	{
		sf::Sprite sprite;
	};

	struct TextureCoord
	{
		sf::IntRect texCoord;
	};

	struct Hitbox
	{
		sf::Vector2f hitbox;
	};

	struct Speed
	{
		float speed;
	};

	struct Healt
	{
		int maxHealt;
		int currentHealt;
		int healtRegen;
	};

	struct Mana
	{
		int maxMana;
		int currentMana;
		int manaRegen;
	};

	struct Damage
	{
		int meleeDamage;
		int magicDamage;
	};

	struct Defence
	{
		int meleeDefence;
		int magicDefence;
	};

	struct Luck
	{
		int luck;
	};

	struct Animation
	{
		sf::Vector2i currentAnimationRange;
		std::vector<sf::Vector2i> AnimationFrames;
		uint8_t lastAnimationFrame;
		float animationSpeed;
		float totalProgress;
		uint8_t lastAnimationFrameCheck;
	};

	struct Inventory
	{
		sf::Clock clock;
		bool showInventory;
		sf::Time cooldownTime = sf::seconds(0.4f);
	};
}