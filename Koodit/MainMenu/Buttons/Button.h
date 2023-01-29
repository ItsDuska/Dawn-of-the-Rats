#pragma once
#include <SFML/Graphics.hpp>
#include "../../Visuals/Texts/Text.h"
#include "../../GameManager/States/StateMachine.h"
#include <iostream>

/*

Parent class of Buttons
Has the main functions of buttons like drawing, activating it and stuff
buttonFunction can be overrited so new types of buttons can be added

*/

class Button
{
private:
	sf::RectangleShape *button;
	sf::Color color;
	Text *text;
	sf::Int8 getButtonColor(int mainColor, int secondColor);
	virtual void buttonFunction(State* state) = 0;
	void initButton(sf::RectangleShape *currentButton, sf::Vector2f position, std::string title, sf::Int8 charSize);
public:
	Button(sf::Vector2f position,sf::Vector2f size, sf::Color color, std::string title);
	~Button();
	void render(sf::RenderTarget *window);
	void checkMousePos(sf::Vector2f mousePos, State* state);
};
