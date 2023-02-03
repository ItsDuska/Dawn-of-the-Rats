#pragma once
#include "WorldCreator.h"
#include <SFML/Graphics.hpp>

//a Tilemap for a chunk.
class Chunk : public sf::Drawable, public sf::Transformable
{
private:
	sf::VertexArray chunk;
	sf::Vector2i chunkCord;
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
public:
	Chunk(sf::Vector2i gridSize, int seed, float threshold, sf::Vector2f tileSize);
};

