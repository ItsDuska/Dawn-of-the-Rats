#pragma once
#include "../Chunk/Chunk.h"


//Handles a 2d array of chunks (The whole world)
class ChunkManager
{
private:
	int seed;
	float threshold;
	sf::Vector2f tileSize;
	sf::Vector2f windowSize;
	const int8_t BLOCK_SIZE = 16;
	//const sf::Vector2i mapSize = { 5,11 };
	sf::Vector2i gridSize;

	//Settings
	const int renderDistance = 1;

	std::vector<std::unique_ptr<Chunk>> chunks;
	std::vector<sf::Vector2i> chunkCords;
	ThreadPool* threadPool;

	sf::Vector2i currentChunk;
	sf::Vector2i previousChunk = {-1,0};

	bool loaded = false;
	const sf::Vector2i neighborPositions[8] = {  {-1,-1}, {-1,0}, {-1,1},    {0,-1}, {0,1},     {1,-1},  {1,0}, {1,1}  };

	//void save();
	//void load();
	float distance(sf::Vector2i currentChunk, sf::Vector2i otherChunk);
	void addChunk(sf::Vector2i chunkPosition);
	void removeChunk(int index);
	bool isInWindow(sf::View *view, sf::Vector2f chunkPosition);

	// new way
	int getChunkPositionIndex(std::vector<sf::Vector2i>*list, sf::Vector2i position);
	void handleChunks();
	
public:
	void update(sf::View *view,sf::Vector2f playerPos);
	void render(sf::RenderTarget* window);
	ChunkManager(sf::Vector2f windowSize, int seed, float threshold,ThreadPool *threadPool);
	~ChunkManager();
};

