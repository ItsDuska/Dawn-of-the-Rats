#pragma once
#include <SFML/Graphics.hpp>
#include "../MainMenu/MainMenu.h"

class Game
{
private:
	sf::RenderWindow* window;
	sf::Event sfEvent;
	MainMenu *menu;
	void initWindow();
	void updateSFMLEvents();
	void update();
	void render();
public:
	Game();
	~Game();
	void run();
};

