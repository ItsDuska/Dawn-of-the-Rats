#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>


class MainMenu
{
private:
	sf::Texture texture;
	sf::Sprite BackGround;
	int screenWidht;
	int screenHeight;
	void initBackGround();
public:
	MainMenu(int width, int height);
	void update();
	void render(sf::RenderTarget* window);
};

