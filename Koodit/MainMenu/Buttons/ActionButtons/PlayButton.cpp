#include "PlayButton.h"


PlayButton::PlayButton(sf::Vector2f position, sf::Vector2f size, sf::Color color, std::string title) : Button(position, size, color, title)
{
}

void PlayButton::buttonFunction(State* state) 
{
	state->changeStateTo = 2;
}
