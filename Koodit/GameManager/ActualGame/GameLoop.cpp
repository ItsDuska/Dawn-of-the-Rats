#include "GameLoop.h"

//funny init function that represents a constructor.
void ActualGame::init()
{
	this->changeStateTo = 2;
	const int8_t BLOCK_SIZE = 32;
	sf::Vector2i chunkSize = {(int) windowSize.x / BLOCK_SIZE, (int) windowSize.y / BLOCK_SIZE };
	this->chunk = new Chunk(chunkSize, 9631, 0.45f, sf::Vector2f(BLOCK_SIZE,BLOCK_SIZE));
		AssetManager::loadTexture("Blocks", "Kuvat/NewSprites/Block.png");
}

//update function for the game loop.
void ActualGame::update(float dt, State* state)
{
	this->player.update();
}

//rendering function for the game loop.
void ActualGame::render(sf::RenderTarget* window)
{
	this->player.render(window);
	window->draw(*chunk);
}

ActualGame::ActualGame(sf::Vector2f windowSize)
{
	this->windowSize = windowSize;
	chunk = nullptr;
}

ActualGame::~ActualGame()
{
	delete this->chunk;
}
