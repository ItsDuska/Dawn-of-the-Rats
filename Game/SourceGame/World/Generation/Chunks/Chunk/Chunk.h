#pragma once

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/VertexBuffer.hpp>
#include <vector>
//#include "World/WorldData/WorldData.h"

//a Tilemap for a chunk.
struct Chunk
{	
	sf::Vector2i chunkCoord;
	bool isDrawable;
	std::vector<std::vector<bool>> blockMap;
	sf::VertexBuffer chunk;
};

