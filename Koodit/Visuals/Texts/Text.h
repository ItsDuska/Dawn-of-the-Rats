#pragma once
#include "SFML/Graphics.hpp"
#include <iostream>

class Text
{
private:
	sf::Font font;
public:
	sf::Text text;
	Text(sf::Int8 charSize, std::string title, sf::Vector2f position);
};

