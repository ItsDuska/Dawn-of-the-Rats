#pragma once
#include "../MainMenu/MainMenu.h"
#include "States/StateMachine.h"
#include "GameState/GameLoop.h"
#include <chrono> 


//The mainGameLoop that handles everything aka the "base class."
class Game
{
private:
	sf::RenderWindow* window;
	sf::Event sfEvent;
	StateMachine states;
	//MainMenu *menu;
	int currentState;
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

