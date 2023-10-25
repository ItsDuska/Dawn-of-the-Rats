#pragma once
#include <GameStates/State.h>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Shader.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Audio/Music.hpp>
#include <string>
#include <memory>

class AnimationHandler;
class AssetManager;
class PlayButton;
class ExitButton;


//The main menu state.
class MainMenu : public State
{
private:
	sf::Sprite rat;
	sf::Sprite logo;
	sf::Shader shader;
	sf::Clock clock;
	sf::RectangleShape background;
	std::unique_ptr<AnimationHandler> rats;
	sf::Music music;
	AssetManager& assetManager;

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

