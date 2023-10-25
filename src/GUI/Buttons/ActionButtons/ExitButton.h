#pragma once
#include "../Button.h"
#include "GameStates/State.h"

class ExitButton : public Button
{
public:
	ExitButton(sf::Vector2f position, sf::Vector2f size, sf::Color color, std::string title, AssetManager& assetManager);
	void buttonFunction(State* state);
};

 