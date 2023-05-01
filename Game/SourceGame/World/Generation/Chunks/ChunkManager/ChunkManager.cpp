#include "ChunkManager.h"

void ChunkManager::addChunk(sf::Vector2i chunkPosition)
{ 
    this->chunkCords.push_back(chunkPosition);

    std::unique_ptr<Chunk> chunk = std::make_unique<Chunk>();
    chunk->chunkCoord = chunkPosition;
    chunk->isDrawable = false;
    chunk->chunk.setPrimitiveType(sf::Quads);
    chunk->chunk.create(static_cast<size_t>(this->gridSize.y) * gridSize.x * 4);
    chunk->chunk.setUsage(sf::VertexBuffer::Stream);
    this->chunks.push_back(std::move(chunk));
    
    threadPool->enqueue([this,x = this->chunks.back().get()]() {this->buildChunk(x); });
    std::cout << "Added chunk at position " << chunkPosition.x << " Y  " << chunkPosition.y <<" X" "\n";
}

float ChunkManager::distance(sf::Vector2i currentChunk, sf::Vector2i otherChunk)
{
    return (float) std::sqrt(std::pow((otherChunk.x - currentChunk.x), 2.f) + std::pow((otherChunk.y - currentChunk.y), 2.f));
}

void ChunkManager::removeChunk(int index)
{
    std::cout << "Deleted a chunk at position " << this->chunks[index]->chunkCoord.x << " Y  " << this->chunks[index]->chunkCoord.y << " X\n";
    this->chunks.erase(this->chunks.begin() + index);
    this->chunkCords.erase(this->chunkCords.begin() + index); 
}

void ChunkManager::buildChunk(Chunk* chunk)
{
    std::cout << "Thread Started\n";

    ChunkBuilder chunkBuilder;
    chunkBuilder.buildChunk(chunk->chunk, this->gridSize,
        this->seed, this->threshold,this->tileSize, chunk->chunkCoord);

    chunk->chunk.setUsage(sf::VertexBuffer::Static);
    std::cout << "amogus";
    chunk->blockMap = chunkBuilder.getBlockMap();
    chunk->isDrawable = true;

    std::cout << "Thread Ended\n";
}

bool ChunkManager::isInWindow(sf::View *view, sf::Vector2f chunkPosition)
{
    sf::FloatRect currentView(view->getCenter() - view->getSize() / 2.f, view->getSize());
    sf::FloatRect chunkRect(chunkPosition, view->getSize());
    return chunkRect.intersects(currentView);
} 

void ChunkManager::update(sf::View *view, sf::Vector2f playerPos)
{
    this->currentChunk = {(int) std::floor((playerPos.y / (gridSize.y*tileSize.y))),(int)std::floor((playerPos.x / (gridSize.x*tileSize.x))) };

    if (this->previousChunk != this->currentChunk)
    {
        if (!this->loaded)
        {
            std::cout << "\nuus chunk\n";
            handleChunks();
        }
    }
    else
    {
        this->loaded = false;
    }
    this->previousChunk = this->currentChunk;

    //tähän kato että onko ikkunan sisällä
    
}

void ChunkManager::render(sf::RenderTarget& target) const
{
    for (const auto& chunk : this->chunks)
    {
        if (!chunk->isDrawable) { continue; }
        target.draw(chunk->chunk, &AssetManager::getTexture("Blocks"));
    }
}

ChunkManager::ChunkManager(sf::Vector2f windowSize, int seed, float threshold, ThreadPool *threadPool)
{
    this->windowSize = windowSize;
    this->seed = seed;
    this->threshold = threshold;
    this->tileSize = { 32.f, 32.f };
    //this->gridSize = sf::Vector2i((int)this->windowSize.x / this->BLOCK_SIZE, (int)this->windowSize.y / this->BLOCK_SIZE);

    this->gridSize = sf::Vector2i(std::floor(chunkSize / this->BLOCK_SIZE), std::floor(chunkSize / this->BLOCK_SIZE));

    this->threadPool = threadPool;
}

ChunkManager::~ChunkManager()
{
    while (!this->chunks.empty())
    {
        this->chunks.pop_back();
    }
}

//Checks if chunk cordinate is loaded. Returns the index if its found, otherwise it returns -1 if its not in the list.
int ChunkManager::getChunkPositionIndex(std::vector<sf::Vector2i>*list, sf::Vector2i position)
{
    std::vector<sf::Vector2i>::iterator iteratorThing;
    iteratorThing = std::find(list->begin(), list->end(), position);

    if (iteratorThing != list->end())
    {   //löyty 
        return (int) (iteratorThing - list->begin());
    }
    else 
    { // ei löytynyt
        return -1;
    }
}

void ChunkManager::handleChunks()
{
    const int renderBonds = (this->renderDistance * 2) + 1;
    std::vector<sf::Vector2i> loadingCoords;
    sf::Vector2i tempChunkCord;

    for (int x = 0; x < renderBonds; x++)
    {
        for (int y = 0; y < renderBonds; y++)
        {
            tempChunkCord = { 
                (x + 1) - ((int)std::round(renderBonds / 2)) + currentChunk.x,
                (y + 1) - ((int)std::round(renderBonds / 2)) + currentChunk.y };

            loadingCoords.push_back(tempChunkCord);

            if (this->getChunkPositionIndex(&this->chunkCords,tempChunkCord) == -1)
            {
                this->addChunk(tempChunkCord);
            }
        }
    }

    std::vector<sf::Vector2i> deletingChunks;

    for (sf::Vector2i position : this->chunkCords)
    {
        //loading cord
        if (this->getChunkPositionIndex(&loadingCoords, position) == -1)
        {
            deletingChunks.push_back(position);
        }
    }

    for (sf::Vector2i position : deletingChunks)
    {
        this->removeChunk(this->getChunkPositionIndex(&this->chunkCords,position));
    }

    this->loaded = true;
    
}
