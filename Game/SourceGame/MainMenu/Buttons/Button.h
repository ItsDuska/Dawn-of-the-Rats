#pragma once
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Window/Mouse.hpp>
#include "Assets/Texts/Text.h"
#include "System/GameStates/StateMachine.h"
#include "Assets/Sounds/SoundManager.h"
#include "Assets/Textures/AssetManager.h"
//#include <iostream>

/*

Parent class of Buttons
Has the main functions of buttons like drawing, activating it and stuff
buttonFunction can be overrited so new types of buttons can be added

*/

class Button
{
private:
	sf::Sprite sprite;
	sf::Color color;
	bool isSoundPlayed;
	engine::Text text;
	sf::Sound sound;
	sf::Int8 getButtonColor(int mainColor, int secondColor);
	virtual void buttonFunction(State* state) = 0;
public:
	Button(sf::Vector2f position,sf::Vector2f size, sf::Color color, std::string title);
	~Button();
	void render(sf::RenderTarget *window);
	void checkMousePos(sf::Vector2f mousePos, State* state);
};
