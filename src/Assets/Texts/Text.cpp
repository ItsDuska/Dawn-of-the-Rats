#include "Text.h"



void engine::Text::setText(sf::Int8 charSize,std::string title,sf::Vector2f position)
{
	this->text.setFont(Fonts::getFont());
	this->text.setCharacterSize(charSize);
	this->text.setString(title);
	this->text.setOrigin(this->text.getGlobalBounds().width / 2, this->text.getGlobalBounds().height / 2);
	this->text.setPosition(position);
}

void engine::Text::changeString(std::string& string)
{
	this->text.setString(string);
}

sf::Text& engine::Text::getText()
{
	return this->text;
}

