#pragma once
#include "WorldCreator.h"
#include "../../../Utils/ThreadPool/ThreadPool.h"
#include <memory>
//#include <SFML/Graphics.hpp>

//a Tilemap for a chunk.
class Chunk : public sf::Drawable, public sf::Transformable
{
private:
	//const int MAX_THREADS_FOR_CHUNKS = 4;
	sf::VertexArray chunk;
	sf::Vector2i gridSize;
	int seed;
	float threshold;
	bool isDrawable;
	sf::Vector2f tileSize;
	sf::Vector2i chunkCoord;
	//sf::Thread thread;
	void createChunk();
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
public:
	Chunk(sf::Vector2i gridSize, int seed, float threshold, sf::Vector2f tileSize, sf::Vector2i chunkCoord,ThreadPool *threadPool);
	void setDrawable(bool drawable);
	bool getDrawable();
	sf::Vector2i getChunkPosition();

};

