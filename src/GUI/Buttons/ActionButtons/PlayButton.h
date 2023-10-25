#pragma once
#include "../Button.h"
#include "GameStates/State.h"


class PlayButton : public Button
{
public:
    PlayButton(sf::Vector2f position, sf::Vector2f size, sf::Color color, std::string title, AssetManager& assetManager);
    void buttonFunction(State* state); 
};

