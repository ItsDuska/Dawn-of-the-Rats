#pragma once
#include "Chunk.h"

//Handles a 2d array of chunks (The whole world)
class ChunkManager
{
private:
	int seed;
	float threshold;
	sf::Vector2i tileSize;
	sf::Vector2i windowSize;
	const sf::Vector2i mapSize = { 5,11 };
	sf::Vector2i gridSize;
	std::vector<Chunk*> chunks;

	//void save();
	//void load();
	void addChunk(sf::Vector2i chunkPosition);
	void removeChunk();
	bool isInWindow(sf::Vector2f playerPosition);
	
public:
	void update(sf::Vector2f playerPosition, sf::View view);
	ChunkManager(sf::Vector2i windowSize, int seed, float threshold, sf::Vector2i gridSize);
	~ChunkManager();
};

