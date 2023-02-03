#pragma once
#include "Chunk.h"

//Handles everything about world generation and stuff.
class WorldManager
{
private:
	sf::Vector2i mapSize = { 5,11 };
	std::vector<std::vector<Chunk*>> world;
};

