#pragma once
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Clock.hpp>


namespace component
{
	struct Gravity
	{
		sf::Vector2f force;
	};

	struct RigidBody
	{
		const float maxVelocity;
		sf::Vector2f velocity;
		sf::Vector2f direction;
		float acceleration;
		float deceleration;
	};

	struct HitBox
	{
		sf::Vector2f box;
	};

	struct Transform
	{
		sf::Vector2f position;
		sf::Vector2f scale;
		
	};

	struct Image
	{
		sf::Sprite sprite;
	};

	struct TextureCoord
	{
		sf::FloatRect textureRect;
	};

	struct Speed
	{
		float speed;
	};

	struct Healt
	{
		int MAXHEALT;
		int currentHealt;
		int healtRegen;
	};

	struct Mana
	{
		int MAX_MANA;
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
		sf::Vector2<uint8_t> currentAnimationRange;
		std::vector<sf::Vector2<uint8_t>> AnimationFrames;
		uint8_t lastFrame;
		uint8_t totalFrames;
		uint8_t startingFrame;
		float animationSpeed;
		float delay;
		float totalProgress;
		bool facingLeft;
	};

	struct Inventory
	{
		sf::Clock clock;
		bool showInventory;
		const sf::Time cooldownTime = sf::seconds(0.4f);
	};
}