#pragma once
#include <map>
#include <SFML/Graphics/Texture.hpp>
#include "../AssetConfig.h"

class AssetManager
{
public:
	AssetManager(const AssetManager&) = delete;
	static AssetManager& get()
	{
		static AssetManager instance;
		return instance;
	}

	static sf::Texture& getTexture(std::string name)
	{
		return get().IgetTexture(name);
	}

	static void loadTexture(std::string name, std::string fileName)
	{
		get().IloadTexture(name, fileName);
	}

	static std::vector<sf::Vector2i> getframeIndexes(std::string name)
	{
		return get().IgetframeIndexes(name);
	}

private:
	std::map<std::string, sf::Texture> _textures;
	AssetManager(){}

	sf::Texture& IgetTexture(std::string name)
	{
		return this->_textures.at(name);
	}

	void IloadTexture(std::string name, std::string fileName)
	{
		sf::Texture texture;

		if (!texture.loadFromFile(ASSETS_PATH+"Sprites/"+fileName))
		{
			return;
		}
		this->_textures[name] = texture;
	}

	std::vector<sf::Vector2i> IgetframeIndexes(std::string name)
	{
		return this->_frameCounts.at(name);
	}

	std::map <std::string, std::vector<sf::Vector2i>> _frameCounts = { // kaikkien animaatioiden alku ja loppu framet.
		{"Player", {sf::Vector2i(0,6),sf::Vector2i(7,16),sf::Vector2i(17,22),sf::Vector2i(23,23),sf::Vector2i(24,38)}}
	};
};
