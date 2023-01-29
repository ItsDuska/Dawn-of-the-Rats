#pragma once
#include <SFML/Graphics.hpp>
#include "../MainMenu/MainMenu.h"
#include "States/StateMachine.h"
#include "ActualGame/ActualGame.h"
#include <chrono> 

class Game
{
private:
	sf::RenderWindow* window;
	sf::Event sfEvent;
	StateMachine states;
	//MainMenu *menu;
	sf::Clock deltaClock;
	void initWindow();
	void changeStates();
	void updateSFMLEvents();
	void update();
	void render();
public:
	Game();
	~Game();
	void run();
};

