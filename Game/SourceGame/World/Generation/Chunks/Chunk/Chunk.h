#pragma once
#include "../ChunkBuilder/ChunkBuilder.h"
#include "System/ThreadPool/ThreadPool.h"
#include <memory>
//#include <SFML/Graphics.hpp>

//a Tilemap for a chunk.
class Chunk : public sf::Drawable, public sf::Transformable
{
private:
	//const int MAX_THREADS_FOR_CHUNKS = 4;
	sf::VertexBuffer chunk;
	sf::Vector2i gridSize;
	int seed;
	float threshold;
	bool isDrawable;
	sf::Vector2f tileSize;
	sf::Vector2i chunkCoord;
	// get funktio muualla näille ?
	std::vector<std::vector<bool>> blockMap;

	//sf::Thread thread;
	void createChunk();
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
public:
	Chunk(sf::Vector2i gridSize, int seed, float threshold, sf::Vector2f tileSize, sf::Vector2i chunkCoord,ThreadPool *threadPool);
	void setDrawable(bool drawable);
	bool getDrawable();
	sf::Vector2i getChunkPosition();

};

