#pragma once
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Vector2.hpp>
#include "Assets/AssetConfig.h"
#include <vector>
#include <map>
#include <iostream>
#include <memory>

/*
TODO:
-Oisko erase funktio joka poistaa halutun tekstuurin.
-Muuta koko class että se ei olisi singleton.
...Singletonit ovat kakkoja ja näiden tilalle voitaisiin vain heittää classin refrenssiä ympäriin.


*/

/*
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
	std::map<std::string, std::unique_ptr<sf::Texture>> _textures;
	AssetManager(){}

	sf::Texture& IgetTexture(std::string name)
	{
		return *_textures.at(name).get();
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
			path = ASSETS_PATH + "Sprites\\" + fileName;
		}

		if (!texture.loadFromFile(path)) // TÄä on ongelma
		{
			std::cout << "\n ERROR: BRUH????????\n"; 
			return;
		}		
	
		//this->_textures[name] = std::make_unique<sf::Texture>(texture);
		this->_textures[name] = std::make_unique<sf::Texture>(texture);
	}


	void IClear()
	{
		this->_textures.clear();
		//this->_frameCounts.clear();
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
*/

class AssetManager
{
public:

	sf::Texture& getTexture(std::string name)
	{
		return _textures.at(name);
	}

	void loadTexture(std::string name, std::string fileName, bool enableFullPath = false)
	{
		sf::Texture texture;

		std::string path;

		if (enableFullPath)
		{
			path = fileName;
		}
		else
		{
			path = ASSETS_PATH + "Sprites\\" + fileName;
		}

		std::cout << "\nPATH: " << path << "\n";

		if (!texture.loadFromFile(path)) // TÄä on ongelma
		{
			std::cout << "\n ERROR: BRUH????????\n";
			return;
		}

		this->_textures[name] = texture;
	}

	std::vector<sf::Vector2i> getframeIndexes(std::string name)
	{
		return this->_frameCounts.at(name);
	}

	void clear()
	{
		this->_textures.clear();
	}

	void remove(std::string name)
	{
		this->_textures.erase(name);
	}

private:
	std::map<std::string, sf::Texture> _textures;

	std::map<std::string, std::vector<sf::Vector2i>> _frameCounts = { // kaikkien animaatioiden alku ja loppu framet.
		{"Player", {sf::Vector2i(0,5),sf::Vector2i(6,15),sf::Vector2i(16,20),sf::Vector2i(20,23),sf::Vector2i(24,38)}},
		{"PlayerWeapon", {sf::Vector2i(0,7)}}
	};
};