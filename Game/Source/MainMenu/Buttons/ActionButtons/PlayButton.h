#pragma once

#include "../Button.h"

class PlayButton : public Button
{
public:
    PlayButton(sf::Vector2f position, sf::Vector2f size, sf::Color color, std::string title);
    void buttonFunction(State* state);
    
};

