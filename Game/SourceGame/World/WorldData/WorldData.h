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