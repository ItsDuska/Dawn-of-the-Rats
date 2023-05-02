#pragma once
#include <iostream>

enum class Biome : int8_t
{
	CORRUPTED,
	LUSH,
	DRIPSTONE,
	FROSTY,
};

enum class BlockType : int8_t
{
	Air,
	Grass,
	Rock
};


struct Block
{
	bool isBlock;
	bool isSolid;
	BlockType blockType;
};


struct ChunkSettings
{
	sf::Vector2f tileSize;
	sf::Vector2i gridSize;
	const int CHUNK_SIZE = 200;
	const int BLOCK_SIZE = 16;
	const int RENDERDISTANCE = 2;
};