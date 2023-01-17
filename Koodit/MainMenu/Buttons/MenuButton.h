#pragma once
#include <SFML/Graphics.hpp>
#include "../../Font/Font.h"
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
	sf::Text text;
	GameFont font;
	void initButton(sf::RectangleShape *currentButton, sf::Vector2f position);
public:
	Button(sf::Vector2f position,sf::Vector2f size, sf::Color color, std::string title);
	~Button();
	void render(sf::RenderTarget *window);
	void checkMousePos(sf::Vector2f mousePos);
	virtual void buttonFunction() = 0;
};
