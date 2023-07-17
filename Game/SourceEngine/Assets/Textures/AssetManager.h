#pragma once
#include <map>
#include <SFML/Graphics/Texture.hpp>
#include <vector>
#include <SFML/System/Vector2.hpp>
#include "../AssetConfig.h"

/*
TODO:
-Oisko erase funktio joka poistaa halutun tekstuurin.
-Muuta koko class ett‰ se ei olisi singleton.
...Singletonit ovat kakkoja ja n‰iden tilalle voitaisiin vain heitt‰‰ classin refrenssi‰ ymp‰riin.


*/


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

	static void loadTexture(std::string name, std::string fileName, bool enableFullPath = false)
	{
		get().IloadTexture(name, fileName, enableFullPath);
	}

	static std::vector<sf::Vector2i> getframeIndexes(std::string name)
	{
		return get().IgetframeIndexes(name);
	}

	static void clear()
	{
		get().IClear();
	}

private:
	std::map<std::string, sf::Texture> _textures;
	AssetManager(){}

	sf::Texture& IgetTexture(std::string name)
	{
		return this->_textures.at(name);
	}

	void IloadTexture(std::string name, std::string fileName,bool enableFullPath)
	{
		sf::Texture texture;

		std::string path;
		
		if (enableFullPath)
		{
			path = fileName;
		}
		else
		{
			path = ASSETS_PATH + "Sprites/" + fileName;
		}

		if (!texture.loadFromFile(path))
		{
			return;
		}
		this->_textures[name] = texture;
	}


	void IClear()
	{
		this->_textures.clear();
		this->_frameCounts.clear();
	}


	std::vector<sf::Vector2i> IgetframeIndexes(std::string name)
	{
		return this->_frameCounts.at(name);
	}

	std::map<std::string, std::vector<sf::Vector2i>> _frameCounts = { // kaikkien animaatioiden alku ja loppu framet.
		{"Player", {sf::Vector2i(0,5),sf::Vector2i(6,15),sf::Vector2i(16,20),sf::Vector2i(20,23),sf::Vector2i(24,38)}},
		{"PlayerWeapon", {sf::Vector2i(0,7)}}
	};
};
