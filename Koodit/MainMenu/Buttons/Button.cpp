#include "Button.h"

Button::~Button()
{
	delete this->button;
	delete this->text;
}

void Button::render(sf::RenderTarget *window)
{
	window->draw(*this->button);
	window->draw(this->text->text);
}

void Button::initButton(sf::RectangleShape *currentButton,sf::Vector2f position, std::string title, sf::Int8 charSize)
{
	currentButton->setPosition(position);
	currentButton->setFillColor(color);
	currentButton->setOutlineColor(sf::Color::White);
	currentButton->setOutlineThickness(2);
	this->text = new Text(charSize, title, sf::Vector2f(position.x + position.x / 10, position.y + position.y / 10));
}

Button::Button(sf::Vector2f position, sf::Vector2f size, sf::Color color, std::string title)
{
	this->button = new sf::RectangleShape(size);
	this->initButton(this->button,position,title,50);
	this->color = color;
}

sf::Int8 Button::getButtonColor(int mainColor, int secondColor)
{
	return (sf::Int8)(mainColor + secondColor) / 2;
}

// Check if mouse is on the button and change the color
void Button::checkMousePos(sf::Vector2f mousePos, State* state)
{
	if (!this->button->getGlobalBounds().contains(mousePos))
	{
		this->button->setFillColor(this->color);
		return;
	}

	//klick check here
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		this->buttonFunction(state);
	}
	this->button->setFillColor(sf::Color(
		getButtonColor(this->color.r,255),
		getButtonColor(this->color.g, 255),
		getButtonColor(this->color.b, 255),
		200)
	);
}		

