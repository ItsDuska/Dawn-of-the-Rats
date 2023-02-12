# pragma once
# include <iostream>
# include "../PerlinNoice/PerlineNoice.hpp"
# include <SFML/System/Vector2.hpp>
#include <SFML/System/Vector2.hpp>

// generates a 2d array of zeros and ones. one is a block and zero is nothing.
class CaveGeneration
{
private:
	float threshold;
	sf::Vector2i gridSize;
	std::vector < std::vector<bool> > cave;
	PerlinNoise perlinNoice;
	void generateCave(sf::Vector2i chunkCoord);
public:
	~CaveGeneration();
	CaveGeneration(int seed, float threshold, sf::Vector2i gridSize, sf::Vector2i chunkCoord);
	bool getCaveBlock(sf::Vector2i position);
};