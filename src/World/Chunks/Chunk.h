#pragma once
#include "World/WorldData.h"
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/VertexBuffer.hpp>
#include <vector>

//a Tilemap for a chunk.
struct Chunk
{	
	sf::Vector2i chunkCoord;
	bool isDrawable = NULL;
	std::vector<std::vector<Block>> blockMap;
	sf::VertexBuffer chunk;
	sf::RectangleShape rect;
};

