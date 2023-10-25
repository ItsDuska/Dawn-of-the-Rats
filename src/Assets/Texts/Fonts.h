#pragma once
#include <iostream>
#include <SFML/Graphics/Font.hpp>
#include <filesystem>
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
		// / "Fonts\\yoster.ttf";


		if (!font.loadFromFile(ASSETS_PATH + "Fonts\\yoster.ttf"))
		{
			std::cout << "ERROR: Failed reading font from a file!\n";
		}
	}
	sf::Font& IgetFont()
	{
		return this->font;
	}

};