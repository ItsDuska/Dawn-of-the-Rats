#pragma once
#include <SFML/Graphics.hpp>
#include "../MainMenu/MainMenu.h"
//#include <chrono> 

class Game
{
private:
	sf::RenderWindow* window;
	sf::Event sfEvent;
	MainMenu *menu;
	sf::Clock deltaClock;
	void initWindow();
	void updateSFMLEvents();
	void update();
	void render();
public:
	Game();
	~Game();
	void run();
};

