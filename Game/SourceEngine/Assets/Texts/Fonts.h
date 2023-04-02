#pragma once
#include <iostream>
#include <SFML/Graphics/Font.hpp>
#include "../AssetConfig.h"

class Fonts
{
public:
	Fonts(const Fonts&) = delete;
	static Fonts& get()
	{
		static Fonts instance;
		return instance;
	}
	static void initFont()
	{
		get().IloadFont();
	}
	
	static sf::Font& getFont()
	{
		return get().IgetFont();
	}
private:
	sf::Font font;
	Fonts() {}

	void IloadFont()
	{
		if (!font.loadFromFile(ASSETS_PATH+"Fonts/yoster.ttf"))
		{
			std::cout << "Font Error";
		}
	}
	sf::Font& IgetFont()
	{
		return this->font;
	}
};