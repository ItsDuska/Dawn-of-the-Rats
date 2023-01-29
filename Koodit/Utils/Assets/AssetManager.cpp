#include "AssetManager.h"

AssetManager::AssetManager()
{
}

AssetManager::~AssetManager()
{
}

void AssetManager::loadTexture(std::string name, std::string fileName)
{
	sf::Texture texture;

	if (!texture.loadFromFile(fileName))
	{
		return;
	}
	this->_textures[name] = texture;
}

sf::Texture& AssetManager::getTexture(std::string name)
{
	return this->_textures.at(name); //
}

void AssetManager::loadFont(std::string name, std::string fileName)
{
	sf::Font font;

	if (!font.loadFromFile(fileName))
	{
		return;
	}
	this->_fonts[name] = font;
}

sf::Font& AssetManager::getFont(std::string name)
{
	return this->_fonts.at(name);
}
