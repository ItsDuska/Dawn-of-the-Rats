#pragma once
#include "System/GameStates/StateMachine.h"
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/Image.hpp>
#include <chrono> 
#include <memory>
#include "Assets/Sounds/SoundManager.h"
#include "Assets/Textures/AssetManager.h"



//The mainGameLoop that handles everything aka the "base class."
class Game
{
protected:
	sf::Image image;
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

