#pragma once
#include "../ChunkBuilder/ChunkBuilder.h"
#include "System/ThreadPool/ThreadPool.h"
#include <memory>
#include <SFML/Graphics/RectangleShape.hpp>
#include "World/WorldData/WorldData.h"
//#include <SFML/Graphics.hpp>

//a Tilemap for a chunk.
class Chunk : public sf::Drawable, public sf::Transformable
{
private:
	//const int MAX_THREADS_FOR_CHUNKS = 4;
	sf::VertexBuffer chunk;
	int seed;
	float threshold;
	bool isDrawable;
	// get funktio muualla näille ?

	

	//sf::Thread thread;
	void createChunk();
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
public:
	Chunk(sf::Vector2i gridSize, int seed, float threshold, sf::Vector2f tileSize, sf::Vector2i chunkCoord,ThreadPool *threadPool);
	void setDrawable(bool drawable);
	bool getDrawable();
	sf::Vector2i getChunkPosition();
	std::vector<std::vector<bool>> blockMap;
	sf::Vector2i gridSize;
	sf::Vector2f tileSize;
	sf::Vector2i chunkCoord;

};

