#pragma once
#include "World/Generation/Chunks/Chunk/Chunk.h"
#include "World/Generation/Chunks/ChunkBuilder/ChunkBuilder.h"
#include "System/ThreadPool/ThreadPool.h"

//Handles a 2d array of chunks (The whole world)
class ChunkManager
{
private:
	int seed;
	float threshold;
	sf::Vector2f tileSize;
	sf::Vector2f windowSize;
	const int8_t BLOCK_SIZE = 16;
	sf::Vector2i gridSize;
	const int chunkSize = 200;
	const int renderDistance = 2;
	sf::Vector2f calcChunkSize;

	std::vector<std::unique_ptr<Chunk>> chunks;
	std::vector<sf::Vector2i> chunkCords;
	ThreadPool* threadPool;

	sf::Vector2i currentChunk;
	sf::Vector2i previousChunk = {-1,0};

	bool loaded = false;



	float distance(sf::Vector2i currentChunk, sf::Vector2i otherChunk);
	void addChunk(sf::Vector2i chunkPosition);
	void removeChunk(int index);
	void buildChunk(Chunk *chunk);
	bool isInWindow(sf::View *view, sf::Vector2i chunkPosition);

	int getChunkPositionIndex(std::vector<sf::Vector2i>*list, sf::Vector2i position);
	void handleChunks();
	
public:
	void update(sf::View *view,sf::Vector2f playerPos);
	
	virtual void render(sf::RenderTarget& target );
	ChunkManager(sf::Vector2f windowSize, int seed, float threshold,ThreadPool *threadPool);
	~ChunkManager();
};

