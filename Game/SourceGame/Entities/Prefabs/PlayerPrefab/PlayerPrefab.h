#pragma once
#include "System/ECS/Coordinator/Cordinator.h"
#include "Assets/Textures/AssetManager.h"

//Player is always the first entity in ECS entity array 
class PlayerPreFab
{
public:
	static void createPlayer(Coordinator& entityManager, uint32_t& entity)
	{
		AssetManager::loadTexture("Player", "NewSprites/PlayerSheet.png");

		entity = entityManager.createEntity(); 

		entityManager.addComponent(entity, Component::Transform{
			sf::Vector2f(1000,500),
			sf::Vector2f(0,0),
			false});
		entityManager.addComponent(entity, Component::RigidBody{
			9.f,
			1.8f,
			0.7f,
			{0.f,0.f},
			{0.f,0.f}});
		entityManager.addComponent(entity, Component::Image{});

		//entityManager.addComponent(entity, Component::Hitbox{});

		entityManager.addComponent(entity, Component::Speed{ 0.5f });
		entityManager.addComponent(entity, Component::Animation{
			{0,6},
			AssetManager::getframeIndexes("Player"),
			0,
			0.1f,
			0,
			6});
																		   // x, y, (frameSize)
		entityManager.addComponent(entity, Component::TextureCoord{ sf::IntRect(0,0,16,16) });
		//INVENTORY VIELÄ JA SEN JÄLKEEN TEE SYSTEM INIT UUDELLEE

		auto& image = entityManager.getComponent<Component::Image>(entity);
		image.sprite.setTexture(AssetManager::getTexture("Player"));
		image.sprite.setTextureRect(sf::IntRect(0, 0, 16, 16));
		image.sprite.setOrigin({ image.sprite.getGlobalBounds().width / 2, image.sprite.getGlobalBounds().height / 2 });
		image.sprite.scale(8.f, 8.f);
		
	}


};