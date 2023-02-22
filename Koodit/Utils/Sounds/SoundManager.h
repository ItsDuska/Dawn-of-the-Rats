#pragma once
#include <map>
#include <SFML/Audio.hpp>
#include <iostream>

class SoundManager
{
public:
	SoundManager(const SoundManager&) = delete;
	static SoundManager& get()
	{
		static SoundManager instance;
		return instance;
	}

	static sf::SoundBuffer& getSound(std::string name)
	{
		return get().IgetSound(name);
	}

	static void loadSound(std::string name, std::string fileName)
	{
		get().IloadSound(name, fileName);
	}


private:
	std::map<std::string, sf::SoundBuffer> _sounds;

	SoundManager() {}

	sf::SoundBuffer& IgetSound(std::string name)
	{
		return this->_sounds.at(name);
	}

	void IloadSound(std::string name, std::string fileName)
	{
		sf::SoundBuffer soundBuffer;

		if (!soundBuffer.loadFromFile(fileName))
		{
			std::cout << "errror on loading sound";
			return;
		}
	
		
		this->_sounds[name] = soundBuffer;
	}
};
