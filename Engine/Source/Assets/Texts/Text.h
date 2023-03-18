#pragma once
#include <SFML/Graphics/Text.hpp>
#include "Fonts.h"
#include <iostream>

namespace engine
{
	class Text
	{
		private:
		sf::Text text;
		public:
		void setText(sf::Int8 charSize, std::string title, sf::Vector2f position);
		void changeString(std::string string);
		sf::Text& getText();
	};
}
