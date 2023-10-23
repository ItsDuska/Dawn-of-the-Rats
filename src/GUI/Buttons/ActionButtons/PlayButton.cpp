#include "PlayButton.h"


PlayButton::PlayButton(sf::Vector2f position, sf::Vector2f size, sf::Color color, std::string title,AssetManager& assetManager) : Button(position, size, color, title,assetManager)
{
}

void PlayButton::buttonFunction(State* state) 
{
	state->changeStateTo = 2;
}
