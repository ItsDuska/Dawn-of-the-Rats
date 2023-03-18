#pragma once
#include "../System/GameStates/StateMachine.h"
#include "SFML/Window/Event.hpp"
#include <chrono> 
#include <memory>




//The mainGameLoop that handles everything aka the "base class."
class Game
{
protected:
	sf::RenderWindow* window;
	sf::Event sfEvent;
	StateMachine states;
	int currentState;
	sf::Clock deltaClock;
	void initWindow();
	virtual void changeStates();
	void updateSFMLEvents();
	void update();
	void render();
public:
	virtual void init();
	~Game();
	void run();
};

