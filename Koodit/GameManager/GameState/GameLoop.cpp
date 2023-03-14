#include "GameLoop.h"

//funny init function that represents a constructor.
void ActualGame::init()
{
	this->changeStateTo = 2;
	AssetManager::loadTexture("Blocks", "Kuvat/NewSprites/GrassyBlock.png");
}

//update function for the game loop.
void ActualGame::update(float dt, State* state)
{
	this->camera.setCenter(this->player.getPosition());
	this->chunkManager.update(&this->camera, this->player.getPosition());
	this->player.update();
}

//rendering function for the game loop.
void ActualGame::render(sf::RenderTarget* window)
{
	//std::chrono::time_point<std::chrono::system_clock> start, end;
	//start = std::chrono::system_clock::now();
	
	//World stuff rendering
	window->setView(this->camera);
	this->chunkManager.render(window);
	this->player.render(window);

	//Piirrä tän jälkeen GUI asiat.
	window->setView(window->getDefaultView());
	this->player.renderInventory(window);

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
