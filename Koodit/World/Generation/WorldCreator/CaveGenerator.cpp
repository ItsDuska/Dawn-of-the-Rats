#include "CaveGenerator.h"

CaveGeneration::CaveGeneration(int seed, float threshold, sf::Vector2i gridSize)
	:perlinNoice(seed)
{
	this->threshold = threshold;
	this->gridSize = gridSize;
	this->cave.resize(gridSize.y);
	this->generateCave();
}

void CaveGeneration::generateCave()
{
	for (int y = 0; y < this->gridSize.y; y++)
	{
		this->cave[y].resize(this->gridSize.x);
		for (int x = 0; x < this->gridSize.x; x++)
		{
			const double noise = this->perlinNoice.noise(x / 16.0, y / 16.0, 3);
			this->cave[y][x] = (noise <= this->threshold);
		}
	}
}

std::vector<std::vector<bool>>& CaveGeneration::getCave()
{
	return this->cave;
}
