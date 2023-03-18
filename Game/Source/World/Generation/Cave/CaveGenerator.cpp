#include "CaveGenerator.h"

CaveGeneration::~CaveGeneration()
{
}

CaveGeneration::CaveGeneration(int seed, float threshold, sf::Vector2i gridSize, sf::Vector2i chunkCoord)
	: perlinNoice(seed)
{
	this->threshold = (double) threshold;
	this->gridSize = gridSize;
	this->cave.resize(gridSize.y);
	this->generateCave(chunkCoord);
}

//Tänne funktio joka generoi tunneleita????

void CaveGeneration::generateCave(sf::Vector2i chunkCoord)
{
	const sf::Vector2i WORLD_POSITION = { chunkCoord.x * gridSize.x, chunkCoord.y * gridSize.y };

	for (int y = 0; y < this->gridSize.y; y++)
	{
		this->cave[y].resize(this->gridSize.x);
		for (int x = 0; x < this->gridSize.x; x++)
		{
			const double noise = this->perlinNoice.noise((double) (WORLD_POSITION.x + x) / 16.0, (double) (WORLD_POSITION.y + y) / 16.0, 3.0);
			this->cave[y][x] = (noise <= this->threshold);
		}
	}
}

bool CaveGeneration::getCaveBlock(sf::Vector2i position)
{
	return this->cave[position.y][position.x];
}

std::vector<std::vector<bool>> CaveGeneration::getCaveMap()
{
	return this->cave;
}