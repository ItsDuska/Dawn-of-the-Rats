#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>


class MainMenu
{
private:
	std::string backGroundsNames[6] = { "Tausta1.png", "Tausta2.png", "Tausta3.png",
		"Tausta3.png", "Tausta4.png", "Tausta5.png" };
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

