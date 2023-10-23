#pragma once
#include <iostream>
#include <SFML/System/Vector2.hpp>

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
	sf::Vector2i gridSize;		//64 64
	const sf::Vector2f tileSize { 64.f, 64.f };
	const int CHUNK_SIZE = 200;
	const int BLOCK_SIZE = 16;
	const int RENDERDISTANCE = 1; // 2 on paras
};