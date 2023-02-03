#include "ExitButton.h"

ExitButton::ExitButton(sf::Vector2f position, sf::Vector2f size, sf::Color color, std::string title) :Button(position, size, color, title)
{
}

void ExitButton::buttonFunction(State* state)
{
	//std::exit(EXIT_FAILURE);
	state->exit = true;
}
