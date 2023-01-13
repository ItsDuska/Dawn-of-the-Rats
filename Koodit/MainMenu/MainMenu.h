#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "../Utils/Animation/AnimationHandler.h"

class MainMenu
{
private:
	std::vector<std::string> backGroundsNames = { "Tausta1.png", "Tausta2.png", "Tausta3.png",
		"Tausta3.png", "Tausta4.png", "Tausta5.png" };
	sf::Texture texture;
	sf::Sprite BackGround;
	AnimationHandler *animationHandle;

	int screenWidht;
	int screenHeight;
	void initBackGround();
public:
	MainMenu(int width, int height);
	void update();
	void render(sf::RenderTarget* window);
};

