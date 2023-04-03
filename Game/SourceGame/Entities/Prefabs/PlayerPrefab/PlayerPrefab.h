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
		AssetManager::loadTexture("Inventory", "NewSprites/Inventory.png");
		AssetManager::loadTexture("InventoryItems", "NewSprites/GUI_ITEM_SPRITES.png");
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
		
		entityManager.addComponent(entity, Component::Inventory{
			{}," ",{0,0},{},0,false,{},false,sf::seconds(0.4f)});

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
		
		auto& inventory = entityManager.getComponent<Component::Inventory>(entity);

		inventory.background.setTexture(AssetManager::getTexture("Inventory"));

		const sf::Vector2f spriteSize = {
			inventory.background.getGlobalBounds().width, 
			inventory.background.getGlobalBounds().height 
		};

		inventory.background.setOrigin(spriteSize.x / 2.f, spriteSize.y / 2.f);
		inventory.background.setPosition(
			sf::VideoMode::getDesktopMode().width / 2.f,
			sf::VideoMode::getDesktopMode().height / 2.f
		);

		inventory.background.scale(
			std::round((sf::VideoMode::getDesktopMode().height / spriteSize.y) - 2.f),
			std::round((sf::VideoMode::getDesktopMode().height / spriteSize.y) - 2.f)
		);

		inventory.stats.setText(30, "TempText", 
			sf::Vector2f(sf::VideoMode::getDesktopMode().width / 2.25f,
			inventory.background.getPosition().y / 2.f)
		);
		inventory.clock.restart();
		
	}


};