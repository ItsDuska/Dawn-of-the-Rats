#include "CaveGenerator.h"

CaveGeneration::~CaveGeneration()
{
}

CaveGeneration::CaveGeneration(int seed, float threshold, sf::Vector2i gridSize, sf::Vector2i chunkCoord)
	: perlinNoice(seed)
{
	this->threshold = threshold;
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
			const float noise = this->perlinNoice.noise((WORLD_POSITION.x + x) / 16.0f, (WORLD_POSITION.y + y) / 16.0f, 3);
			this->cave[y][x] = (noise <= this->threshold);
		}
	}
}

bool CaveGeneration::getCaveBlock(sf::Vector2i position)
{
	return this->cave[position.y][position.x];
}
