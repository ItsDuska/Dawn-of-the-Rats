#include "Button.h"

Button::~Button()
{
	this->sound.stop();
}

void Button::render(sf::RenderTarget *window)
{
	window->draw(this->button);
	window->draw(this->text.getText());
}

void Button::initButton(sf::Vector2f position)
{
	this->button.setPosition(position);
	this->button.setFillColor(color);
	this->button.setOutlineColor(sf::Color::White);
	this->button.setOutlineThickness(2);
}

Button::Button(sf::Vector2f position, sf::Vector2f size, sf::Color color, std::string title) 
{
	this->text.setText(50, title, sf::Vector2f(position.x + size.x / 2, position.y + size.y / 2));
	this->button.setSize(size);
	this->initButton(position);
	this->color = color;
	this->sound.setBuffer(SoundManager::getSound("Button"));
}

sf::Int8 Button::getButtonColor(int mainColor, int secondColor)
{
	return (sf::Int8)(mainColor + secondColor) / 2;
}

//Check if mouse is on top of the button and change the button color to a whiter color. Also activates the function of the button that can be overwritten.
void Button::checkMousePos(sf::Vector2f mousePos, State* state)
{
	if (!this->button.getGlobalBounds().contains(mousePos))
	{
		this->button.setFillColor(this->color);
		this->isSoundPlayed = false;
		return;
	}
	
	if(!this->isSoundPlayed && this->sound.getStatus() == sf::Sound::Stopped)
	{
		this->sound.play();
	}
	
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		this->buttonFunction(state);
	}
	this->button.setFillColor(sf::Color(
		getButtonColor(this->color.r,255),
		getButtonColor(this->color.g, 255),
		getButtonColor(this->color.b, 255),
		128)
	);
	this->isSoundPlayed = true;
}		

