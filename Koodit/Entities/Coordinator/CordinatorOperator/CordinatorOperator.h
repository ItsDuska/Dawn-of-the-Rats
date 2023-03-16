#pragma once
#include "../Cordinator.h"


enum class SystemType : int8_t
{
	RENDER,
	PHYSICS,
	COLLISION
};

class EntityHelper
{
public:
	static void initComponents(Coordinator* entityManager)
	{
		//entityManager->registerComponent<Gravity>();
		//entityManager->registerComponent<RigidBody>();
		entityManager->registerComponent<Transform>();
		entityManager->registerComponent<Image>();
	}

	template<typename SYSTEM>
	static void initSystem(Coordinator* entityManager, SYSTEM *system, SystemType type)
	{
		Signature signature;
		switch (type)
		{
		case SystemType::RENDER:
			signature.set(entityManager->GetComponentType<Transform>());
			signature.set(entityManager->GetComponentType<Image>());
			break;
		case SystemType::PHYSICS:
			break;
		case SystemType::COLLISION:
			break;
		default:
			break;
		}

		entityManager->SetSystemSignature<SYSTEM>(signature);
	}
	static void createEntity(Coordinator* entityManager,std::vector<uint32_t> &entities)
	{
		for (auto& entity : entities)
		{
			entity = entityManager->createEntity();

			entityManager->addComponent(entity, Transform{ 
				sf::Vector2f(500.f + rand() % 1000,500.f),
				sf::Vector2f(1.f,1.f),
				0.f });

			entityManager->addComponent(entity, Image{});
			entityManager->getComponent<Image>(entity).sprite.setTexture(AssetManager::getTexture("Shocked"));
		}
	}
};



