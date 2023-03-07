#pragma once
#include "../Utils/Sounds/SoundManager.h"
#include "../Utils/Animation/AnimationHandler.h"
#include "../GameManager/States/StateMachine.h"
#include "../Utils/Assets/AssetManager.h"
#include "Buttons/ActionButtons/ExitButton.h"
#include "Buttons/ActionButtons/PlayButton.h"
//#include <memory>

//The main menu state.
class MainMenu : public State
{
private:
	const std::string ratPath = "Kuvat/MainMenuStuff/Rat/RatSpriteSheet.png";
	sf::Sprite rat;
	sf::Shader shader;
	sf::Clock clock;
	sf::RectangleShape background;
	std::unique_ptr<AnimationHandler> rats;
	//AssetManager assets;

	//Buttons
	std::unique_ptr <PlayButton> playButton;
	std::unique_ptr <ExitButton> exitButton;

	sf::Vector2f mousePos = {0,0};
	sf::Vector2f screenSize;
	void initBackGround();
	
public:
	MainMenu(sf::Vector2f screenSize);
	~MainMenu();
	void init() {};
	void update(float dt, State* state);
	void render(sf::RenderTarget* window);
};

