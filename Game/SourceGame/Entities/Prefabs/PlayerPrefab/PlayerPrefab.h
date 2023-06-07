#pragma once
#include "System/ECS/Coordinator/Cordinator.h"
#include "Assets/Textures/AssetManager.h"
#include <SFML/Window/VideoMode.hpp>

//Player is always the first entity in ECS entity array 
class PlayerPreFab
{
public:
	static void createPlayer(Coordinator& entityManager, uint32_t& entity)
	{
		AssetManager::loadTexture("Player", "NewSprites/PlayerSheet.png");
		entity = entityManager.createEntity(); 
		entityManager.addComponent(entity, Component::Transform{
			sf::Vector2f(0,600),
			sf::Vector2f(100,100)
			});
		entityManager.addComponent(entity, Component::RigidBody{
			9.f,
			1.8f,
			0.6f,
			{0.f,0.f},
			{0.f,0.f}});
		entityManager.addComponent(entity, Component::Image{});
		entityManager.addComponent(entity, Component::Speed{ 0.5f ,12.5f});
		entityManager.addComponent(entity, Component::Collider{});
		entityManager.addComponent(entity, Component::Animation{
			{0,6},
			AssetManager::getframeIndexes("Player"),
			0,
			0.1f,
			0,
			6,
			false});
																		   // x, y, (frameSize)
		entityManager.addComponent(entity, Component::TextureCoord{ sf::IntRect(0,0,16,16) });
		
		entityManager.addComponent(entity, Component::State{ Component::EntityStates::IDLE,Component::EntityStates::IDLE,false,false,false});


		entityManager.addComponent(entity, Component::Inventory{
			" ",{0,0},0,false,false,true,sf::seconds(0.4f)});

		entityManager.addComponent(entity, Component::Health{ 100,100,2 });
		entityManager.addComponent(entity, Component::Mana{ 100,100,2 });
		entityManager.addComponent(entity, Component::Damage{ 15,10 });
		entityManager.addComponent(entity, Component::Defence{ 5,2 });
		entityManager.addComponent(entity, Component::Luck{ 1 });

		auto& image = entityManager.getComponent<Component::Image>(entity);
		image.sprite.setTexture(AssetManager::getTexture("Player"));
		image.sprite.setTextureRect(sf::IntRect(0, 0, 16, 16));
		image.sprite.setOrigin({ image.sprite.getGlobalBounds().width / 2, image.sprite.getGlobalBounds().height / 2 });
		image.sprite.scale(8.f, 8.f);

		float newPos = 0.5f *image.sprite.getGlobalBounds().width;

		entityManager.addComponent(entity, Component::Hitbox{ sf::Vector2f(newPos, image.sprite.getGlobalBounds().height)
			,sf::Vector2f((image.sprite.getGlobalBounds().width / 2) - newPos, image.sprite.getGlobalBounds().height / 2)});
		
	}
};