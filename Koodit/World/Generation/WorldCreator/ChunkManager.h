#pragma once
#include "Chunk.h"

//Handles a 2d array of chunks (The whole world)
class ChunkManager
{
private:
	int seed;
	float threshold;
	sf::Vector2f tileSize;
	sf::Vector2f windowSize;
	const int8_t BLOCK_SIZE = 16;
	const sf::Vector2i mapSize = { 5,11 };
	sf::Vector2i gridSize;
	std::vector<Chunk*> chunks;
	sf::Vector2i currentChunk;
	const sf::Vector2i neighborPositions[8] = {  {-1,-1}, {-1,0}, {-1,1},    {0,-1}, {0,1},     {1,-1},  {1,0}, {1,1}  };

	//void save();
	//void load();
	float distance(sf::Vector2i currentChunk, sf::Vector2i otherChunk);
	void addChunk(sf::Vector2i chunkPosition);
	void removeChunk(int index);
	bool isInWindow(sf::View *view, sf::Vector2f chunkPosition);
	
public:
	void update(sf::View *view);
	void render(sf::RenderTarget* window);
	ChunkManager(sf::Vector2f windowSize, int seed, float threshold);
	~ChunkManager();
};

