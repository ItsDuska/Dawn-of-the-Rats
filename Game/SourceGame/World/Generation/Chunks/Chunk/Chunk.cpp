#include "Chunk.h"


int clamp(int value, int min, int max) {
	return std::max(min, std::min(max, value));
}


// initialize the chunk by creating it with Perlin noise
Chunk::Chunk(sf::Vector2i gridSize, int seed, float threshold, sf::Vector2f tileSize, sf::Vector2i chunkCoord,ThreadPool *threadPool)
	: gridSize(gridSize), seed(seed), threshold(threshold), tileSize(tileSize),chunkCoord(chunkCoord), isDrawable(false)
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
	
	ChunkBuilder chunkBuilder;
	chunkBuilder.buildChunk(this->chunk,this->gridSize, this->seed, this->threshold, this->tileSize,this->chunkCoord);
	this->chunk.setUsage(sf::VertexBuffer::Static);
	this->blockMap = chunkBuilder.getBlockMap(); // tää heitti erroria
	this->isDrawable = true;

	//FOR DEBUGIN

	this->rect.setPosition(
		((this->chunkCoord.y - 1) * gridSize.y) * tileSize.y,
		((this->chunkCoord.x - 1) * gridSize.x)* tileSize.x);

	this->rect.setSize(
		sf::Vector2f((float)gridSize.x * tileSize.x,
		(float)gridSize.y * tileSize.y));




	this->rect.setFillColor(sf::Color(rand() % 255, rand() % 255, rand() % 255, 20));
	this->rect.setOutlineColor(sf::Color::White);
	this->rect.setOutlineThickness(1);

	std::cout << "Thread Ended\n";

}

//override draw function so the VertexArray can use a texture
void Chunk::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	if (!this->isDrawable) { return; }
    //states.transform *= getTransform();
    states.texture = &AssetManager::getTexture("Blocks");
    target.draw(chunk, states);
	//target.draw(this->rect);
}
