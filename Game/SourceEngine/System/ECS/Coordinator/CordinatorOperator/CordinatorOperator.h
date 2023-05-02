#pragma once
#include "../Cordinator.h"
#include "System/ECS/Systems/Systems.h"
#include <SFML/Graphics/Rect.hpp>

enum class SystemType : int8_t
{
	RENDER,
	MOVEMENT,
	ANIMATION,
	PHYSICS,
	COLLISION, 
	PLAYER_INPUT,
	INVENTORY
	
	
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
	}

	
	static void initSystem(Coordinator& entityManager, Systems& entitySystems)
	{
		entitySystems.render = entityManager.registerSystem<RenderSystem>();
		entitySystems.movement = entityManager.registerSystem<MovementSystem>();
		entitySystems.playerInput = entityManager.registerSystem<PlayerInputSystem>();
		entitySystems.animation = entityManager.registerSystem<AnimationSystem>();
		entitySystems.inventory = entityManager.registerSystem<InventorySystem>();
		entitySystems.collision = entityManager.registerSystem<CollisionSystem>();



		//JOKAINEN COMBO PITÄÄ INITTAAA SIIS
		setSignature(entityManager, *entitySystems.render.get(), SystemType::RENDER);
		setSignature(entityManager, *entitySystems.movement.get(), SystemType::MOVEMENT);
		setSignature(entityManager, *entitySystems.playerInput.get(), SystemType::PLAYER_INPUT);
		setSignature(entityManager, *entitySystems.animation.get(), SystemType::ANIMATION);
		setSignature(entityManager, *entitySystems.inventory.get(), SystemType::INVENTORY);
		setSignature(entityManager, *entitySystems.collision.get(), SystemType::COLLISION);
		
	}


	static void createEntity(Coordinator* entityManager,std::vector<uint32_t> &entities)
	{
		for (int i = 1; i<entities.size(); i++)
		{
			entities[i] = entityManager->createEntity();

			entityManager->addComponent(entities[i], Component::Transform{
				sf::Vector2f(500.f + rand() % 1000,500.f),
				sf::Vector2f(0,0),
				false
				});
			
			entityManager->addComponent(entities[i], Component::Image{});
			auto& enemy = entityManager->getComponent<Component::Image>(entities[i]);
			enemy.sprite.setTexture(AssetManager::getTexture("Shocked"));
			entityManager->addComponent(entities[i], Component::TextureCoord{sf::IntRect(0,0,
				(int)enemy.sprite.getLocalBounds().width,(int)enemy.sprite.getLocalBounds().height)});
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
			break;
		case SystemType::MOVEMENT:
			signature.set(entityManager.getComponentType<Component::RigidBody>());
			signature.set(entityManager.getComponentType<Component::Transform>());
			break;
		case SystemType::ANIMATION:
			signature.set(entityManager.getComponentType<Component::Animation>());
			signature.set(entityManager.getComponentType<Component::TextureCoord>());
			break;
		case SystemType::PLAYER_INPUT:
			signature.set(entityManager.getComponentType<Component::RigidBody>());
			signature.set(entityManager.getComponentType<Component::Transform>());
			signature.set(entityManager.getComponentType<Component::Animation>());
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
		default:
			break;
		}
		entityManager.setSystemSignature<SYSTEM>(signature);
	}

};



