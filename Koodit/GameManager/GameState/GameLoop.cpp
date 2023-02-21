#include "GameLoop.h"

//funny init function that represents a constructor.
void ActualGame::init()
{
	this->changeStateTo = 2;
	//const int8_t BLOCK_SIZE = 16;
	//sf::Vector2i chunkSize = {(int) this->windowSize.x / BLOCK_SIZE, (int) this->windowSize.y / BLOCK_SIZE };
	//std::cout << chunkSize.x << " " << chunkSize.y << "     ";
	//this->chunk = new Chunk(chunkSize, 9631, 0.45f, sf::Vector2f(BLOCK_SIZE,BLOCK_SIZE));
	AssetManager::loadTexture("Blocks", "Kuvat/NewSprites/Block.png");
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
	//World stuff rendering
	window->setView(this->camera);
	this->chunkManager.render(window);
	this->player.render(window);

	//Piirrä tän jälkeen GUI asiat.
	window->setView(window->getDefaultView());

}

ActualGame::ActualGame(sf::Vector2f windowSize)
	:chunkManager(windowSize,47786,0.45f)
{
	this->windowSize = windowSize;
	this->camera.reset(sf::FloatRect(this->player.getPosition(), windowSize));
	
}

ActualGame::~ActualGame()
{
	
}
