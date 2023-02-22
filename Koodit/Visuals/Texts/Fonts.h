#pragma once
#include <iostream>
#include <SFML/Graphics/Font.hpp>

class Fonts
{
public:
	Fonts(const Fonts&) = delete;
	static Fonts& get()
	{
		static Fonts instance;
		return instance;
	}
	static void loadFont()
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
		if (!font.loadFromFile("Fonts/yoster.ttf"))
		{
			std::cout << "Font Error";
		}
	}
	sf::Font& IgetFont()
	{
		return this->font;
	}
};