#include "ExitButton.h"

ExitButton::ExitButton(sf::Vector2f position, sf::Vector2f size, sf::Color color, std::string title) :Button(position, size, color, title)
{
}

//exits the state.
void ExitButton::buttonFunction(State* state)
{
	state->exit = true;
}
