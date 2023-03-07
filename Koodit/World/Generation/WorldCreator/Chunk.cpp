#include "Chunk.h"

// initialize the chunk by creating it with Perlin noise
Chunk::Chunk(sf::Vector2i gridSize, int seed, float threshold, sf::Vector2f tileSize, sf::Vector2i chunkCoord,ThreadPool *threadPool)
	: gridSize(gridSize), seed(seed), threshold(threshold), tileSize(tileSize),chunkCoord(chunkCoord), isDrawable(true)
{
	this->chunk.setPrimitiveType(sf::Quads);
	this->chunk.create(static_cast<size_t>(gridSize.y) * gridSize.x * 4);
	this->chunk.setUsage(sf::VertexBuffer::Stream);
	threadPool->enqueue([this]() {this->createChunk();});
}

void Chunk::setDrawable(bool drawable)
{
	this->isDrawable = drawable;
}

bool Chunk::getDrawable()
{
	return this->isDrawable;
}

sf::Vector2i Chunk::getChunkPosition()
{
	return this->chunkCoord;
}

void Chunk::createChunk()
{

	std::cout << "Thread Started\n";
	
	WorldCreator worldCreator;
	worldCreator.buildChunk(&this->chunk,this->gridSize, this->seed, this->threshold, this->tileSize,this->chunkCoord);
	this->chunk.setUsage(sf::VertexBuffer::Static);
	std::cout << "Thread Ended\n";

}

//override draw function so the VertexArray can use a texture
void Chunk::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	if (!this->isDrawable) { return; }
    //states.transform *= getTransform();
    states.texture = &AssetManager::getTexture("Blocks");
    target.draw(chunk, states);
}
