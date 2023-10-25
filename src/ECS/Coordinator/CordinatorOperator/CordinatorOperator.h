#pragma once
#include "ECS/Coordinator/Cordinator.h"
#include "ECS/Systems/Systems.h"
#include <SFML/Graphics/Rect.hpp>

enum class SystemType : int8_t
{
	RENDER,
	MOVEMENT,
	ANIMATION,
	ANIMATION_HANDLER,
	PHYSICS,
	COLLISION, 
	PLAYER_INPUT,
	INVENTORY,
	FOLLOW
	
	
};


class EntityHelper
{
public:
	static void initComponents(Coordinator& entityManager)
	{
		

		entityManager.registerComponent<Component::RigidBody>();
		entityManager.registerComponent<Component::Transform>();
		entityManager.registerComponent<Component::Image>();
		entityManager.registerComponent<Component::Animation>();
		entityManager.registerComponent<Component::Speed>();
		entityManager.registerComponent<Component::TextureCoord>();
		entityManager.registerComponent<Component::Inventory>();
		entityManager.registerComponent<Component::Health>();
		entityManager.registerComponent<Component::Mana>();
		entityManager.registerComponent<Component::Damage>();
		entityManager.registerComponent<Component::Defence>();
		entityManager.registerComponent<Component::Luck>();
		entityManager.registerComponent<Component::Hitbox>();
		entityManager.registerComponent<Component::Collider>();
		entityManager.registerComponent<Component::State>();
		entityManager.registerComponent<Component::Tag>();
		entityManager.registerComponent<Component::FollowObject>();
		std::cout << "BUILD: Created Components.\n";
	}

	
	static void initSystem(Coordinator& entityManager, Systems& entitySystems)
	{
		entitySystems.render = entityManager.registerSystem<RenderSystem>();
		entitySystems.movement = entityManager.registerSystem<MovementSystem>();
		entitySystems.playerInput = entityManager.registerSystem<PlayerInputSystem>();
		entitySystems.animation = entityManager.registerSystem<AnimationSystem>();
		entitySystems.animationHandler = entityManager.registerSystem<AnimationHalderSystem>();
		entitySystems.inventory = entityManager.registerSystem<InventorySystem>();
		entitySystems.collision = entityManager.registerSystem<CollisionSystem>();
		entitySystems.follow = entityManager.registerSystem<FollowSystem>();



		//JOKAINEN COMBO PIT�� INITTAAA SIIS
		setSignature(entityManager, *entitySystems.render, SystemType::RENDER);
		setSignature(entityManager, *entitySystems.movement, SystemType::MOVEMENT);
		setSignature(entityManager, *entitySystems.playerInput, SystemType::PLAYER_INPUT);
		setSignature(entityManager, *entitySystems.animation, SystemType::ANIMATION);
		setSignature(entityManager, *entitySystems.animationHandler, SystemType::ANIMATION_HANDLER);
		setSignature(entityManager, *entitySystems.inventory, SystemType::INVENTORY);
		setSignature(entityManager, *entitySystems.collision, SystemType::COLLISION);
		setSignature(entityManager, *entitySystems.follow, SystemType::FOLLOW);
		
		std::cout << "BUILD: Created Systems.\n";
	}


	static void createEntity(Coordinator* entityManager,std::vector<uint32_t> &entities, AssetManager& assetManager)
	{
		for (int i = 2; i<entities.size(); i++)
		{
			entities[i] = entityManager->createEntity();

			entityManager->addComponent(entities[i], Component::Transform{
				sf::Vector2f(rand() % 1000, rand() % 1000),
				sf::Vector2f()
				});
			entityManager->addComponent(entities[i], Component::Hitbox{});


			entityManager->addComponent(entities[i], Component::Image{});
			auto& enemy = entityManager->getComponent<Component::Image>(entities[i]);
			enemy.sprite.setTexture(assetManager.getTexture("Shocked"));
			entityManager->addComponent(entities[i], Component::TextureCoord{sf::IntRect(0,0,
				(int)enemy.sprite.getLocalBounds().width,(int)enemy.sprite.getLocalBounds().height)});
			enemy.sprite.setScale(sf::Vector2f(-5, -5));
		}
	}
private:
	template<typename SYSTEM>
	static void setSignature(Coordinator& entityManager, SYSTEM system, SystemType type)
	{
		Signature signature;
		switch (type)
		{
		case SystemType::RENDER:
			signature.set(entityManager.getComponentType<Component::Transform>());
			signature.set(entityManager.getComponentType<Component::Image>());
			signature.set(entityManager.getComponentType<Component::TextureCoord>());
			signature.set(entityManager.getComponentType<Component::Hitbox>());
			break;
		case SystemType::MOVEMENT:
			signature.set(entityManager.getComponentType<Component::RigidBody>());
			signature.set(entityManager.getComponentType<Component::Transform>());
			break;
		case SystemType::ANIMATION:
			signature.set(entityManager.getComponentType<Component::Animation>());
			signature.set(entityManager.getComponentType<Component::TextureCoord>());
			signature.set(entityManager.getComponentType<Component::State>());
			break;
		case SystemType::ANIMATION_HANDLER:
			signature.set(entityManager.getComponentType<Component::Animation>());
			signature.set(entityManager.getComponentType<Component::State>());
			break;
		case SystemType::PLAYER_INPUT:
			signature.set(entityManager.getComponentType<Component::RigidBody>());
			signature.set(entityManager.getComponentType<Component::Transform>());
			signature.set(entityManager.getComponentType<Component::State>());
			signature.set(entityManager.getComponentType<Component::Speed>());
			signature.set(entityManager.getComponentType<Component::Inventory>());
			break;
		case SystemType::PHYSICS:
			break;
		case SystemType::COLLISION:
			signature.set(entityManager.getComponentType<Component::RigidBody>());
			signature.set(entityManager.getComponentType<Component::Transform>());
			signature.set(entityManager.getComponentType<Component::Hitbox>());
			signature.set(entityManager.getComponentType<Component::Collider>());
			signature.set(entityManager.getComponentType<Component::State>());
			break;
		case SystemType::INVENTORY:
			signature.set(entityManager.getComponentType<Component::Inventory>());
			signature.set(entityManager.getComponentType<Component::Health>());
			signature.set(entityManager.getComponentType<Component::Mana>());
			signature.set(entityManager.getComponentType<Component::Damage>());
			signature.set(entityManager.getComponentType<Component::Defence>());
			signature.set(entityManager.getComponentType<Component::Speed>());
			signature.set(entityManager.getComponentType<Component::Luck>());
			break;
		case SystemType::FOLLOW:
			signature.set(entityManager.getComponentType<Component::FollowObject>());
			signature.set(entityManager.getComponentType<Component::Transform>());
			break;
		default:
			break;
		}
		entityManager.setSystemSignature<SYSTEM>(signature);
	}

};


