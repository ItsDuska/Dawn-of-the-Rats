#pragma once
#include "GameStates/StateMachine.h"
#include "Assets/Sounds/SoundManager.h"
#include "Assets/Textures/AssetManager.h"
#include "GameStates/MainMenuState/MainMenu.h"
#include "GameStates/WorldState/WorldState.h"

#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/Image.hpp>
#include <chrono> 
#include <memory>


//The mainGameLoop that handles everything aka the "base class."
class Game
{
private:
	sf::Image image;
	sf::RenderWindow* window;
	sf::Event sfEvent;
	StateMachine states;
	int currentState;
	sf::Clock deltaClock;
	AssetManager assetManager;

	void initWindow();
	void changeStates();
	void updateSFMLEvents();
	void update();
	void render();
public:
	void init();
	~Game();
	void run();
};

