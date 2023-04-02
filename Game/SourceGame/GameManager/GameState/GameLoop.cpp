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
}

//update function for the game loop.
void ActualGame::update(float dt, State* state)
{
	//this->camera.setCenter(this->player.getPosition());
	this->camera.setCenter(this->entityManager.getComponent<Component::Transform>(this->entities[0]).position);
	this->chunkManager.update(&this->camera, this->entityManager.getComponent<Component::Transform>(this->entities[0]).position);

	////////
	this->systems.playerInput->update(this->entityManager);
	this->systems.movement->update(this->entityManager);
	this->systems.animation->update(this->entityManager);
	this->systems.render->update(this->entityManager);
	////////

	//this->player.update();
}

//rendering function for the game loop.
void ActualGame::render(sf::RenderTarget* window)
{
	//std::chrono::time_point<std::chrono::system_clock> start, end;
	//start = std::chrono::system_clock::now();
	//World stuff rendering
	window->setView(this->camera);
	this->chunkManager.render(window);
	this->systems.render->render(this->entityManager,window);
	//this->player.render(window);

	//Piirrä tän jälkeen GUI asiat.
	window->setView(window->getDefaultView());
	//this->player.renderInventory(window);

	//end = std::chrono::system_clock::now();
	//std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() << "[microsecs]" << std::endl;

}

ActualGame::ActualGame(sf::Vector2f windowSize)
	:chunkManager(windowSize, 47786, 0.45f, &threadPool)
{
	this->windowSize = windowSize;
	this->camera.reset(sf::FloatRect(this->player.getPosition(), windowSize));
	
}

ActualGame::~ActualGame()
{
	
}
