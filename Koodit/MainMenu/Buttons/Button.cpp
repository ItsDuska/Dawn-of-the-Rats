#include "Button.h"

Button::~Button()
{
	delete this->button;
}

void Button::render(sf::RenderTarget *window)
{
	window->draw(*this->button);
}

Button::Button(sf::Vector2f position, sf::Vector2f size, sf::Color color)
{
	this->button = new sf::RectangleShape(size);
	this->button->setPosition(position);
	this->button->setFillColor(color); // tähä alpha value 128
	this->button->setOutlineColor(sf::Color::White);
	this->color = color;
}

// Check if mouse is on the button and change the color and check the click event
void Button::checkMousePos(sf::Vector2f mousePos)
{
	if (!this->button->getGlobalBounds().contains(mousePos))
	{
		this->button->setFillColor(this->color);
		return;
	}

	//klick check here

	this->button->setFillColor(sf::Color(200, 200, 255, 128));
}		
