#include "MenuButton.h"

Button::~Button()
{
	delete this->button;
}

void Button::render(sf::RenderTarget *window)
{
	window->draw(*this->button);
	window->draw(this->text);
}

void Button::initButton(sf::RectangleShape *currentButton,sf::Vector2f position)
{
	currentButton->setPosition(position);
	currentButton->setFillColor(color);
	currentButton->setOutlineColor(sf::Color::White);
	currentButton->setOutlineThickness(2);
}

Button::Button(sf::Vector2f position, sf::Vector2f size, sf::Color color,std::string title)
{
	this->button = new sf::RectangleShape(size);
	this->initButton(this->button,position);
	this->color = color;
	this->text.setFont(this->font.FONT);
	this->text.setCharacterSize(35);
	this->text.setString(title);
	this->text.setPosition(position.x + position.x / 10, position.y + position.y / 2);
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
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		this->buttonFunction();
	}
	this->button->setFillColor(sf::Color(200, 200, 255, 200));
}		
