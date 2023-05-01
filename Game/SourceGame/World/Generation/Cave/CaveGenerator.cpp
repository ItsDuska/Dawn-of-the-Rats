#include "CaveGenerator.h"

CaveGeneration::~CaveGeneration()
{
}

CaveGeneration::CaveGeneration(int seed, float threshold, sf::Vector2i gridSize, sf::Vector2i chunkCoord)
	: perlinNoice(seed)
{
	this->threshold = (double) threshold;
	this->gridSize = gridSize;
	this->cave.resize(size_t(gridSize.y+2));
	this->generateCave(chunkCoord);
}

//Tänne funktio joka generoi tunneleita????

void CaveGeneration::generateCave(sf::Vector2i chunkCoord)
{
	const sf::Vector2i WORLD_POSITION = { chunkCoord.x * gridSize.x, chunkCoord.y * gridSize.y };

	for (int y = 0; y < this->gridSize.y+2; y++)
	{
		this->cave[y].resize(size_t(this->gridSize.x+2));
		for (int x = 0; x < this->gridSize.x+2; x++)
		{
			const double noise = this->perlinNoice.noise((double) (WORLD_POSITION.x + x-1) / 16.0, (double) (WORLD_POSITION.y + y-1) / 16.0, 3.0);
			if ((noise <= this->threshold))
			{
				this->cave[y][x].blockType = BlockType::Grass;
				this->cave[y][x].isBlock = true;
			}
			else {
				this->cave[y][x].blockType = BlockType::Air;
				this->cave[y][x].isBlock = false;
			}
		}
	}
}

Block& CaveGeneration::getCaveBlock(sf::Vector2i position)
{
	return this->cave[position.y][position.x];
}

std::vector<std::vector<Block>> CaveGeneration::getCaveMap()
{
	return this->cave;
}