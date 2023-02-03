#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
class State 
{
public: // 0 = current, 1 = main menu, 2 = Game
	int changeStateTo = 0;
	bool exit = false;
	virtual void init() = 0;
	virtual void update(float deltaTime, State *state) = 0;
	virtual void render(sf::RenderTarget* window) = 0;
	virtual void pause() {};
	virtual void resume() {};
};