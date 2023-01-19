#pragma once
#include "../Button.h"

class ExitButton : public Button
{
public:
	ExitButton(sf::Vector2f position, sf::Vector2f size, sf::Color color, std::string title);
	void buttonFunction();
};

 