#include "GameLoop.h"

//funny init function that represents a constructor.
void ActualGame::init()
{
	this->changeStateTo = 2;
	this->chunk = new Chunk(sf::Vector2i(50, 50), 5579, 0.5f, sf::Vector2f(16,16));
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

ActualGame::ActualGame()
{
	chunk = nullptr;
}

ActualGame::~ActualGame()
{
	delete this->chunk;
}
