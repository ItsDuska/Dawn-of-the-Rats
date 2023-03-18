#pragma once
#include "System/ECS/Coordinator/Cordinator.h"
#include "../Components/Components.h"
#include "Assets/Textures/AssetManager.h"


enum class EntityType : int8_t
{
	PLAYER,
	SLIME,
	SHOCKED,

};

enum class SystemType : int8_t
{
	RENDER,
	PHYSICS,
	COLLISION,
	PLAYER_INPUT,
	INVENTORY,
	ANIMATION
};

class EntityHelper
{
public:
	//Need to be called only once when the program starts. Inits every Component
	static void initComponents(Coordinator* entityManager)
	{
		entityManager->registerComponent<component::Gravity>();
		entityManager->registerComponent<component::RigidBody>();
		entityManager->registerComponent<component::Transform>();
		entityManager->registerComponent<component::Image>();
		entityManager->registerComponent<component::HitBox>();
		entityManager->registerComponent<component::Damage>();
		entityManager->registerComponent<component::Animation>();
		entityManager->registerComponent<component::Defence>();
		entityManager->registerComponent<component::Healt>();
		entityManager->registerComponent<component::Luck>();
		entityManager->registerComponent<component::Mana>();
		entityManager->registerComponent<component::Speed>();
		entityManager->registerComponent<component::TextureCoord>();
	}


	/*
	Tee funktio joka katsoo minkä Entity type on 
	
	
	*/


	template<typename SYSTEM>
	static void initSystem(Coordinator& entityManager, SYSTEM *system, SystemType type)
	{
		Signature signature;
		switch (type)
		{
		case SystemType::RENDER:
			signature.set(entityManager.GetComponentType<component::Transform>());
			signature.set(entityManager.GetComponentType<component::Image>());
			break;
		case SystemType::PHYSICS:
			break;
		case SystemType::COLLISION:
			break;
		case SystemType::PLAYER_INPUT:
			signature.set(entityManager.GetComponentType<component::Animation>());
			signature.set(entityManager.GetComponentType<component::RigidBody>());
			signature.set(entityManager.GetComponentType<component::TextureCoord>());
			signature.set(entityManager.GetComponentType<component::Speed>());
			break;
				
			
		default:
			break;
		} 

		entityManager.SetSystemSignature<SYSTEM>(signature);
	}
	static void createEntity(Coordinator* entityManager,std::vector<uint32_t> &entities)
	{
		//for (auto& entity : entities)`
		for (int i = 0; i<4; i++)
		{
			entities[i] = entityManager->createEntity();

			entityManager->addComponent(entities[i], component::Transform{
				sf::Vector2f(500.f + i*200,800.f),
				sf::Vector2f(1.f,1.f)});

			entityManager->addComponent(entities[i], component::Image{});
			entityManager->getComponent<component::Image>(entities[i]).sprite.setTexture(AssetManager::getTexture("Shocked"));
			entityManager->getComponent<component::Image>(entities[i]).sprite.setScale({ -1,1 });
		}
	}
};



