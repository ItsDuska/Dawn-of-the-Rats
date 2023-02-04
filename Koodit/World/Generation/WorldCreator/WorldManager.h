#pragma once
#include "Chunk.h"

//Handles a 2d array of chunks (The whole world)
class WorldManager
{
private:
	sf::Vector2i mapSize = { 5,11 };
	std::vector<std::vector<Chunk*>> world;
};

