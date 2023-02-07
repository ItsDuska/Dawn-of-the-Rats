#include "GameLoop.h"

//funny init function that represents a constructor.
void ActualGame::init()
{
	this->changeStateTo = 2;
	sf::Vector2i chunkSize = {(int) windowSize.x / 16, (int) windowSize.y / 16 };
	std::cout << chunkSize.x << " " << chunkSize.y << "\n";
	this->chunk = new Chunk(chunkSize, 1579, 0.5f, sf::Vector2f(16,16));
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
