#include "Text.h"

Text::Text(sf::Int8 charSize,std::string title,sf::Vector2f position)
{
	if (!this->font.loadFromFile("Fonts/yoster.ttf"))
	{
		std::cout << "Font Error";
	}

	this->text.setFont(this->font);
	this->text.setCharacterSize(charSize);
	this->text.setString(title);
	this->text.setPosition(position);
}


