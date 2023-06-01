#include "ChunkManager.h"

void ChunkManager::addChunk(sf::Vector2i chunkPosition)
{ 
    this->chunkCords.push_back(chunkPosition);

    std::unique_ptr<Chunk> chunk = std::make_unique<Chunk>();  
    
    chunk->rect.setFillColor(sf::Color(0, 255, 0, 128));
    
       
    chunk->rect.setSize(sf::Vector2f(12 * 64, 12 * 64));
    chunk->rect.setPosition(sf::Vector2f((chunkPosition.y * 12) * 64, (chunkPosition.x * 12) * 64));
    chunk->rect.setOutlineColor(sf::Color::White);
    chunk->rect.setOutlineThickness(1);

    chunk->chunkCoord = chunkPosition;
    chunk->isDrawable = false;
    chunk->chunk.setPrimitiveType(sf::Quads);
    chunk->chunk.create(static_cast<size_t>(this->settings.gridSize.y) * this->settings.gridSize.x * 4);
    chunk->chunk.setUsage(sf::VertexBuffer::Stream);
    this->chunks.push_back(std::move(chunk));
    
    threadPool->enqueue([this,x = this->chunks.back().get()]() {this->buildChunk(x); });
    //std::cout << "Added chunk at position " << chunkPosition.x << " Y  " << chunkPosition.y <<" X" "\n";
}

float ChunkManager::distance(sf::Vector2i currentChunk, sf::Vector2i otherChunk)
{
    return (float) std::sqrt(std::pow((otherChunk.y - currentChunk.y), 2.f) + std::pow((otherChunk.x - currentChunk.x), 2.f));
}

void ChunkManager::removeChunk(int index)
{
    std::cout << "Deleted a chunk at position " << this->chunks[index]->chunkCoord.x << " Y  " << this->chunks[index]->chunkCoord.y << " X\n";
    this->chunks.erase(this->chunks.begin() + index);
    this->chunkCords.erase(this->chunkCords.begin() + index); 
}

void ChunkManager::buildChunk(Chunk* chunk)
{
    //std::cout << "Thread Started\n";

    ChunkBuilder chunkBuilder;
    chunkBuilder.buildChunk(chunk->chunk, this->settings.gridSize,
        this->seed, this->threshold,this->settings.tileSize, chunk->chunkCoord);

    chunk->chunk.setUsage(sf::VertexBuffer::Static);
   // std::cout << "amogus";
    chunk->blockMap = chunkBuilder.getBlockMap();
    chunk->isDrawable = true;

   // std::cout << "Thread Ended\n";
}

bool ChunkManager::isInWindow(sf::View *view, sf::Vector2i chunkPosition)
{
    sf::FloatRect currentView(view->getCenter() - view->getSize() / 2.f, view->getSize());
    sf::FloatRect chunkRect( chunkPosition.y *calcChunkSize.y, chunkPosition.x * calcChunkSize.x, calcChunkSize.y, calcChunkSize.x);
    return chunkRect.intersects(currentView);
} 

void ChunkManager::update(sf::View *view, sf::Vector2f playerPos)
{
    this->currentChunk = {(int) std::floor((playerPos.y / (this->settings.gridSize.y*this->settings.tileSize.y))),
        (int) std::floor((playerPos.x / (this->settings.gridSize.x*this->settings.tileSize.x))) };

   // std::cout << "\n\nCurrent chunk position : " << this->currentChunk.y << "x  " << this->currentChunk.x << "y\n\n";

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

void ChunkManager::render(sf::RenderTarget& target) 
{
    for (const auto& chunk : this->chunks)
    {
        if (!chunk->isDrawable) { continue; }
        target.draw(chunk->chunk, &AssetManager::getTexture("Blocks"));
        //target.draw(chunk->rect);
    }
}

ChunkManager::ChunkManager(sf::Vector2f windowSize, int seed, float threshold, ThreadPool *threadPool)
    : renderBonds((this->settings.RENDERDISTANCE * 2) + 1)
{
    this->windowSize = windowSize;
    this->seed = seed;
    this->threshold = threshold;
    this->settings.tileSize = { 64.f, 64.f };
   
    //this->gridSize = sf::Vector2i((int)this->windowSize.x / this->BLOCK_SIZE, (int)this->windowSize.y / this->BLOCK_SIZE);

    this->settings.gridSize = sf::Vector2i(
        std::floor(this->settings.CHUNK_SIZE / this->settings.BLOCK_SIZE),
        std::floor(this->settings.CHUNK_SIZE / this->settings.BLOCK_SIZE)
    );

    this->threadPool = threadPool;
    this->calcChunkSize =  sf::Vector2f(this->settings.gridSize.x * this->settings.gridSize.x, this->settings.gridSize.y * this->settings.gridSize.y );
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

std::vector<std::unique_ptr<Chunk>>* ChunkManager::getLoadedChunks()
{
    return &this->chunks;
}

void ChunkManager::handleChunks()
{
    
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

    
    for (const auto& chunk : this->chunks)
    {
        //std::cout << "  " << (this->distance(this->currentChunk, chunk.get()->chunkCoord)) << "  ";
        if (std::fabs(this->distance(this->currentChunk, chunk.get()->chunkCoord)) < 2)
        {
            
            chunk.get()->isDrawable = true;
        }
    }
    

    this->loaded = true;
}
