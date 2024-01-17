#pragma once
#include "Assets/Sounds/SoundManager.h"
#include "Assets/Animation/AnimationHandler.h"
#include "GameStates/StateMachine.h"
#include "GUI/Buttons/ActionButtons/ExitButton.h"
#include "GUI/Buttons/ActionButtons/PlayButton.h"
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Shader.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Audio/Music.hpp>
//#include <memory>

//The main menu state.
class MainMenu : public State
{
private:
	const std::string ratPath = "MainMenuStuff/Rat/RatSpriteSheet.png";
	sf::Sprite rat;
	sf::Sprite logo;
	sf::Shader shader;
	sf::Clock clock;
	sf::RectangleShape background;
	std::unique_ptr<AnimationHandler> rats;
	sf::Music music;
	AssetManager& assetManager;

	//AssetManager assets;

	//Buttons
	std::unique_ptr <PlayButton> playButton;
	std::unique_ptr <ExitButton> exitButton;

	sf::Vector2f mousePos;
	sf::Vector2f screenSize;
	void initBackGround();
	
public:
	MainMenu(sf::Vector2f screenSize, AssetManager& assetManager);
	~MainMenu();
	void init() {};
	void update(float dt, State* state);
	void render(sf::RenderTarget* window);
	void onResize(sf::Vector2f size);
	void cleanup();
};

