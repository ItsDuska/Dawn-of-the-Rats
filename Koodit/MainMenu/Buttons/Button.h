#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

/*

Parent class of Buttons
Has the main functions of buttons like activating the click and stuff
Has a function that can be overwrited

*/

class Button
{
private:
	~Button();
	sf::RectangleShape *button;
	sf::Color color;
	virtual void buttonFunction() = 0;


public:
	Button(sf::Vector2f position,sf::Vector2f size, sf::Color color);
	void render(sf::RenderTarget *window);
	void checkMousePos(sf::Vector2f mousePos);

};

