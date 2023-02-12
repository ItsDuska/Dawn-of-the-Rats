#include "ChunkManager.h"

void ChunkManager::addChunk(sf::Vector2i chunkPosition)
{ 
    this->chunks.push_back(new Chunk(this->gridSize, this->seed, this->threshold, this->tileSize,chunkPosition));
    std::cout << chunkPosition.x << " " << chunkPosition.y << "\n";
}

float ChunkManager::distance(sf::Vector2i currentChunk, sf::Vector2i otherChunk)
{
    return (float) std::sqrt(std::pow((otherChunk.x - currentChunk.x), 2.f) + std::pow((otherChunk.y - currentChunk.y), 2.f));
}

void ChunkManager::removeChunk(int index)
{
    delete this->chunks[index];
    this->chunks.erase(this->chunks.begin() + index);
}

bool ChunkManager::isInWindow(sf::View *view, sf::Vector2f chunkPosition)
{
    sf::FloatRect currentView(view->getCenter() - view->getSize() / 2.f, view->getSize());
    sf::FloatRect chunkRect(chunkPosition, view->getSize());
    return chunkRect.intersects(currentView);
} 

void ChunkManager::update(sf::View *view)
{
    this->currentChunk = { (int)(view->getCenter().x / windowSize.x),(int) (view->getCenter().y / windowSize.y) };
  
    for (int i = 0; i < this->chunks.size(); i++)
    {     
        this->chunks[i]->setDrawable(this->isInWindow(view, this->chunks[i]->getPosition()));
        if (this->chunks[i]->getChunkPosition() == this->currentChunk) { continue; }

        if (this->distance(currentChunk, this->chunks[i]->getChunkPosition()) > 1)
        {
            std::cout << " Deleted a chunk at index " << i << "  ";
            this->removeChunk(i);
        }
    }

    if (this->chunks.size() > 8) { return; }

    for (sf::Vector2i neighborChunk : neighborPositions)
    {
        for (int i = 0; i<this->chunks.size(); i++)
        {
            if (this->currentChunk + neighborChunk != this->chunks[i]->getChunkPosition())
            {
                this->addChunk(this->currentChunk + neighborChunk);
                std::cout <<  "    Added a chunk  at index  " << i << "  ";
                break;
            }
        }
    }
}

void ChunkManager::render(sf::RenderTarget* window)
{
    for (Chunk* chunk : this->chunks)
    {
        window->draw(*chunk);
    }
}

ChunkManager::ChunkManager(sf::Vector2f windowSize, int seed, float threshold)
{
    this->windowSize = windowSize;
    this->seed = seed;
    this->threshold = threshold;
    this->tileSize = { 16.f, 16.f };
    this->gridSize = sf::Vector2i((int)this->windowSize.x / this->BLOCK_SIZE, (int)this->windowSize.y / this->BLOCK_SIZE);
    this->addChunk({0,0});
}

ChunkManager::~ChunkManager()
{
    while (!this->chunks.empty())
    {
        delete this->chunks.back();
        this->chunks.pop_back();
    }
}
