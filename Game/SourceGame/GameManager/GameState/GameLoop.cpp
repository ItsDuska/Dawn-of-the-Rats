#include "GameLoop.h"
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

}

//update function for the game loop.
void ActualGame::update(float dt, State* state)
{
	std::chrono::time_point<std::chrono::system_clock> start, end;
	start = std::chrono::system_clock::now();

	sf::Vector2f tempPos = this->entityManager.getComponent<Component::Transform>(this->entities[0]).position;
	
	this->camera.setCenter(sf::Vector2f((int)tempPos.x,tempPos.y));
	this->chunkManager.update(&this->camera, tempPos);

	////////
	this->systems.playerInput->update(this->entityManager);
	this->systems.movement->update(this->entityManager);
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
	//this->player.render(window);

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
