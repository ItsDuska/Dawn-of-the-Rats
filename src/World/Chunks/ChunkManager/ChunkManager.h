#pragma once
#include "World/Chunks/Chunk.h"
#include "World/Chunks/ChunkBuilder/ChunkBuilder.h"
#include "Utils/ThreadPool/ThreadPool.h"
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/View.hpp>
#include <SFML/Graphics/Shader.hpp>

//Handles a 2d array of chunks (The whole world)
class ChunkManager
{
public:
	ChunkSettings settings;
	std::vector<sf::Vector2i> chunkCords;
private:
	int seed;
	float threshold;
	const int renderBonds;

	sf::Vector2f windowSize;
	sf::Vector2f calcChunkSize;

	std::vector<std::unique_ptr<Chunk>> chunks;

	ThreadPool& threadPool;
	sf::Vector2i currentChunk;
	sf::Vector2i previousChunk = {-1,0};
	bool loaded = false;
	sf::RenderStates states;

	float distance(sf::Vector2i currentChunk, sf::Vector2i otherChunk);
	void addChunk(sf::Vector2i chunkPosition);
	void removeChunk(int index);
	void buildChunk(Chunk *chunk);
	bool isInWindow(sf::View *view, sf::Vector2i chunkPosition);
	void handleChunks();
	
public:
	void update(sf::View *view,sf::Vector2f playerPos);
	int getChunkPositionIndex(std::vector<sf::Vector2i>* list, sf::Vector2i position);
	std::vector<std::unique_ptr<Chunk>>* getLoadedChunks();


	void render(sf::RenderTarget& target, sf::Shader* shader = NULL, sf::Vector2f playerPos = sf::Vector2f());
	ChunkManager(sf::Vector2f windowSize, int seed, float threshold,ThreadPool &threadPool, AssetManager& assetManager);
	~ChunkManager();
};

