#include "ChunkManager.h"

void ChunkManager::addChunk(sf::Vector2i chunkPosition)
{
    // add chun to list
    this->chunks.push_back(new Chunk(this->gridSize, this->seed, this->threshold, this->tileSize));
}

void ChunkManager::removeChunk()
{
}

bool ChunkManager::isInWindow(sf::Vector2f playerPosition)
{
    return false;
}

void ChunkManager::update(sf::Vector2f playerPosition, sf::View view)
{
}

ChunkManager::ChunkManager(sf::Vector2i windowSize, int seed, float threshold, sf::Vector2i gridSize)
{
    this->windowSize = windowSize;
    this->seed = seed;
    this->threshold = threshold;
    this->gridSize = gridSize;
    this->addChunk({0,0});
}

ChunkManager::~ChunkManager()
{
}
