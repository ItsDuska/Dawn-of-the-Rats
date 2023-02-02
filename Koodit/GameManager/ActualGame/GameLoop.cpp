#include "GameLoop.h"

void ActualGame::init()
{
}

void ActualGame::update(float dt, State* state)
{
	this->player.update();
}

void ActualGame::render(sf::RenderTarget* window)
{
	this->player.render(window);
}
