#pragma once
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Clock.hpp>
//#include "GUI/Inventory/Item.h"
#include "Assets/Texts/Text.h"
#include <memory>

class Item;

namespace Component
{ 
	enum class EntityStates : std::uint8_t
	{
		WALKING,
		IDLE,
		JUMP,
		FALLING,
		ATTACK,
		TAKE_DAMAGE,
		DEATH
	};

	struct State
	{
		EntityStates currentState;
		EntityStates possibleState;
		bool triggerJump;
		bool facingLeft;
		bool onGround;
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
		sf::Vector2f size;
		sf::Vector2f pos;
	};

	struct Speed
	{
		float speed;
		float jumpingSpeed;
	};

	struct Health
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
		int lastAnimationFrame;
		float animationSpeed;
		float totalProgress;
		int lastAnimationFrameCheck;
		bool finishedAnimation;
	};

	struct Inventory
	{
		std::string statsString;
		sf::Vector2f _originalPosition;
		int _selectedItemIndex;
		bool isSelceted;
		bool showInventory;
		bool updateText;
		sf::Time cooldownTime;
		std::vector<std::shared_ptr<Item>> _items{ };
		sf::Clock clock;
	};
	
	struct Collider
	{
		bool blockCollision;
		bool entityCollision;
	};

	struct Tag
	{
		std::string name;
	};

	struct FollowObject
	{
		std::string name;
		float sinTime;
		float moveSpeed;
		float distanceToObject;
		bool stopFollowing;
		sf::Clock clock;
	};
}