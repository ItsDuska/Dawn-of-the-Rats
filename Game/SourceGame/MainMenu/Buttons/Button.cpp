#include "Button.h"

Button::~Button()
{
	this->sound.stop();
}

void Button::render(sf::RenderTarget *window)
{
	//window->draw(this->button);
	window->draw(this->sprite);
	window->draw(this->text.getText());
	
}

Button::Button(sf::Vector2f position, sf::Vector2f size, sf::Color color, std::string title) 
{
	this->sprite.setTexture(AssetManager::getTexture("Button"));
	this->text.setText(50, title, sf::Vector2f(position.x + size.x / 2, position.y + size.y / 2));
	this->sprite.setScale(4, 4);
	this->sprite.setPosition(position);
	this->color = color;
	this->sound.setBuffer(SoundManager::getSound("Button"));
	this->isSoundPlayed = false;
}

sf::Int8 Button::getButtonColor(int mainColor, int secondColor)
{
	return (sf::Int8)(mainColor + secondColor) / 2;
}

//Check if mouse is on top of the button and change the button color to a whiter color. Also activates the function of the button that can be overwritten.
void Button::checkMousePos(sf::Vector2f mousePos, State* state)
{
	if (!this->sprite.getGlobalBounds().contains(mousePos))
	{
		this->sprite.setColor(sf::Color::White);
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
	this->sprite.setColor(sf::Color(
		getButtonColor(sf::Color::White.r, 255),
		getButtonColor(this->color.g, 255),
		getButtonColor(this->color.b, 255),
		255));
	
	this->isSoundPlayed = true;
}		

