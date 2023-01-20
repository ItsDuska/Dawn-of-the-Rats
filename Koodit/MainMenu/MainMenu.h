#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "../Utils/Animation/AnimationHandler.h"
#include "Buttons/ActionButtons/ExitButton.h"

class MainMenu
{
private:
	std::vector<std::string> backGroundsNames = { "Tausta1.png", "Tausta2.png", "Tausta3.png",
		"Tausta3.png", "Tausta4.png", "Tausta5.png" };
	sf::Texture bgTexture;
	sf::Texture ratSheet;
	sf::Sprite backGround;
	sf::Sprite rat;
	AnimationHandler *backgrounds;
	AnimationHandler *rats;
	//Buttons
	ExitButton* exitButton;

	sf::Vector2f mousePos = {0,0};
	int screenWidht;
	int screenHeight;
	void initBackGround();
	void loadSprites(sf::Texture& texture, sf::Sprite& sprite, std::string path);
public:
	MainMenu(int width, int height);
	~MainMenu();
	void update();
	void render(sf::RenderTarget* window);
};

