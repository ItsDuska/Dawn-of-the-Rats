#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "../Utils/Animation/AnimationHandler.h"
#include "../GameManager/States/StateMachine.h"
#include "../Utils/Assets/AssetManager.h"
#include "Buttons/ActionButtons/ExitButton.h"
#include "Buttons/ActionButtons/PlayButton.h"

class MainMenu : public State
{
private:
	std::string backgroundPath = "Kuvat/MainMenuStuff/Taustat/Tausta1.png";
	std::string ratPath = "Kuvat/MainMenuStuff/Rat/RatSpriteSheet.png";
	sf::Sprite backGround;
	sf::Sprite rat;
	//AnimationHandler *backgrounds;
	AnimationHandler *rats;
	AssetManager assets;
	//Buttons
	PlayButton* playButton;
	ExitButton* exitButton;

	sf::Vector2f mousePos = {0,0};
	int screenWidht;
	int screenHeight;
	void initBackGround();
	
public:
	MainMenu(int width, int height);
	~MainMenu();
	void init() {};
	void update(float dt, State* state);
	void render(sf::RenderTarget* window);
};

