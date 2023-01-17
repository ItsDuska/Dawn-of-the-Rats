#pragma once
#include <SFML/Graphics/Font.hpp>
#include <iostream>
class GameFont
{
public:
	sf::Font FONT;
	GameFont() 
	{
		if (!FONT.loadFromFile("Fonts/yoster.ttf"))
		{
			std::cout << "Font Error";
		}
	}
};
