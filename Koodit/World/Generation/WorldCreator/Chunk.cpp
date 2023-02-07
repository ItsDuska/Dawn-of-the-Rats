#include "Chunk.h"

// initialize the chunk by creating it with Perlin noise
Chunk::Chunk(sf::Vector2i gridSize, int seed, float threshold, sf::Vector2f tileSize)
	:gridSize(gridSize),seed(seed),threshold(threshold),tileSize(tileSize), thread(&Chunk::createChunk,this)
{
	this->chunk.setPrimitiveType(sf::Quads);
	this->chunk.resize(static_cast<size_t>(gridSize.y) * gridSize.x * 4);
	thread.launch();
}

void Chunk::createChunk()
{
	WorldCreator(this->chunk, this->gridSize, this->seed, this->threshold, this->tileSize);
}

//rewrite draw function so the VertexArray can use a texture
void Chunk::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    //states.transform *= getTransform();
    states.texture = &AssetManager::getTexture("Blocks");
    target.draw(chunk, states);
}
