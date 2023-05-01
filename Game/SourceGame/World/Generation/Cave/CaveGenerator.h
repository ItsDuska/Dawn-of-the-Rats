# pragma once
# include "Algorhythms/PerlinNoice/PerlineNoice.hpp"
# include <iostream>
# include <SFML/System/Vector2.hpp>
# include "World/WorldData/WorldData.h"

// generates a 2d array of zeros and ones. one is a block and zero is nothing.
class CaveGeneration
{
private:
	double threshold;
	sf::Vector2i gridSize;
	std::vector < std::vector<Block> > cave;
	PerlinNoise perlinNoice;
	void generateCave(sf::Vector2i chunkCoord);
public:
	~CaveGeneration();
	CaveGeneration(int seed, float threshold, sf::Vector2i gridSize, sf::Vector2i chunkCoord);
	std::vector<std::vector<Block>> getCaveMap();
	Block& getCaveBlock(sf::Vector2i position);
};