﻿#include "GameLoop.h"
//funny init function that represents a constructor.
void ActualGame::init()
{
	this->changeStateTo = 2;
	AssetManager::loadTexture("Blocks", "NewSprites/GrassyBlock.png");
	AssetManager::loadTexture("Shocked", "NewSprites/SHOCKED.jpg");
	//entity hämmeli
	this->entities.resize(MAX_ENTITIES);
	this->entityManager.init();
	
	EntityHelper::initComponents(this->entityManager);
	EntityHelper::initSystem(this->entityManager, this->systems);
	PlayerPreFab::createPlayer(this->entityManager, this->entities[0]);
	EntityHelper::createEntity(&this->entityManager, this->entities);
	this->systems.inventory->addNewItem(this->entityManager);

	this->frameTime.setText(50,"", sf::Vector2f(0,0));
	auto sus = this->entityManager.getComponent < Component::Image>(this->entities[0]).sprite.getGlobalBounds();
	float newPos = 0.5f * sus.width;
	auto& amog = this->entityManager.getComponent < Component::Hitbox>(this->entities[0]);

	this->pelaajaHitBox.setFillColor(sf::Color(0, 0, 255, 128));
	this->pelaajaHitBox.setOutlineColor(sf::Color::White);
	this->pelaajaHitBox.setOutlineThickness(1);
	
	
	//this->pelaajaHitBox.setOrigin({ (sus.width / 2) - newPos / 2, sus.height / 2 });
	//this->pelaajaHitBox.setSize(sf::Vector2f(newPos, sus.height));
	this->pelaajaHitBox.setSize(amog.size);
}

//update function for the game loop.
void ActualGame::update(float dt, State* state)
{
	std::chrono::time_point<std::chrono::system_clock> start, end;
	start = std::chrono::system_clock::now();

	sf::Vector2f tempPos = this->entityManager.getComponent<Component::Transform>(this->entities[0]).position;
	
	this->camera.setCenter(sf::Vector2f((int)tempPos.x,tempPos.y));
	this->chunkManager.update(&this->camera, this->entityManager.getComponent<Component::Transform>(this->entities[0]).futurePosition);
	
	this->pelaajaHitBox.setPosition(this->entityManager.getComponent<Component::Hitbox>(this->entities[0]).pos);

	////////
	this->systems.playerInput->update(this->entityManager);
	this->systems.movement->update(this->entityManager);
	this->systems.collision->update(this->entityManager, this->chunkManager.getLoadedChunks(), this->chunkManager.settings, this->chunkManager.chunkCords);
	this->systems.animation->update(this->entityManager);
	this->systems.render->update(this->entityManager);
	this->systems.inventory->update(this->entityManager);
	////////

	end = std::chrono::system_clock::now();

	if (this->updateText)
		this->updateTime = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
	//std::cout << "Update logic = " << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() << " microseconds" << std::endl;

	//this->player.update();
}

//rendering function for the game loop.
void ActualGame::render(sf::RenderTarget* window)
{
	std::chrono::time_point<std::chrono::system_clock> start, end;
	start = std::chrono::system_clock::now();
	//World stuff rendering

	
	//this->fakeWindow.clear();


	window->setView(this->camera);
	this->chunkManager.render(*window);
	this->systems.render->render(this->entityManager, window);

	window->draw(this->pelaajaHitBox);
	//this->player.render(window);
	this->systems.collision->render(window);

	//Piirrä tän jälkeen GUI asiat.
	window->setView(window->getDefaultView());
	//this->player.renderInventory(window);
	this->systems.inventory->render(this->entityManager, window);
	


	end = std::chrono::system_clock::now();
	std::ostringstream oss;

	if (this->updateText)
	{
		oss << "Game logic: " << this->updateTime.count() << " microseconds\n"
			<< "Rendering logic: " << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() << " microseconds";
		this->tempString = oss.str();
		this->frameTime.changeString(this->tempString);
	}


		//this->frameTime.changeString("Game logic: " + this->updateTime + " mircoseconds\nRendering logic : " + 
			//std::to_string(std::chrono::duration_cast<std::chrono::microseconds>(end - start).count()) + " mircoseconds");

	this->updateText = !this->updateText;
	window->draw(this->frameTime.getText());


}

ActualGame::ActualGame(sf::Vector2f windowSize)
	:chunkManager(windowSize, 47786, 0.45f, &threadPool)
{
	this->windowSize = windowSize;
	this->updateTime = std::chrono::microseconds(0);
	this->camera.reset(sf::FloatRect(sf::Vector2f(0,0), windowSize));
	
}

ActualGame::~ActualGame()
{
	
}
