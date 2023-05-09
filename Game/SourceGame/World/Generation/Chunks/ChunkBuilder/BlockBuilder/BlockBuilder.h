#pragma once
#include <SFML/System/Vector2.hpp>
#include <iostream>


class BlockBuilder
{
public:
	sf::Vector2f getTexCoord(bool* blocks);
	sf::Vector2f getGrassTexCoord(bool* blocks);

	BlockBuilder();
private:
	static const int TEX_COORD_TABLE_SIZE = 46;
	static const int GRASS_TEX_COORD_TABLE_SIZE = 10;
	const int8_t texCoordTable[TEX_COORD_TABLE_SIZE];
	const int8_t grassTexCoordTable[GRASS_TEX_COORD_TABLE_SIZE];

	const bool possibilitiesGrass[GRASS_TEX_COORD_TABLE_SIZE][4] =
	{
		// vasen -> ylä -> ala -> oikea

		// suoraviivat
		{0,0,0,1},
		{1,0,0,0},
		{0,0,1,0},
		{0,1,0,0},
		
		//L muodot
		{1,1,0,0},
		{1,0,1,0},
		{0,1,0,1},
		{0,0,1,1},
		//U muodot
		{1,0,1,1},
		{1,1,0,1},

	};

	const bool possiblities[TEX_COORD_TABLE_SIZE][8] =
	{
		//  0
		{0,0,0
		,0  ,1
		,0,1,1},

		{0,0,1,
		0, 1,
		0,1,1},

		{0,0,0,
		0, 1,
		1,1,1},

		{0,0,1,
		0,  1,
		1,1,1},

		// 1
		{0,0,0,
		1,   0,
		1,1,0},

		{1,0,0,
		1,  0,
		1,1,0},

		{0,0,0,
		1,  0,
		1,1,1},

		{1,0,0,
		1,   0,
		1,1,1},

		//2
		{0,1,1
		,0,  1,
		0,0,0},

		{0,1,1,
		0,   1,
		0,0,1},

		{1,1,1,
		0,   1,
		0,0,0},

		{1,1,1,0,1,0,0,1},

		//3
		{1,1,0
		,1  ,0,
		0,0,0},

		{1,1,0,
		1,  0,
		1,0,0},

		{1,1,1,
		1,  0,
		0,0,0},

		{1,1,1,1,0,1,0,0},

		//4-6
		{0,0,0
		,1,  1,
		1,1,1},

		{0,0,1,
		1, 1,
		1,1,1},

		{1,0,0,
		1, 1,
		1,1,1},

		{1,0,1,
		1, 1,
		1,1,1},

		//7-9
		{1,1,1,
		1   ,1,
		0,0,0},

		{1,1,1,
		1   ,1,
		0,0,1},

		{1,1,1,
		1   ,1,
		1,0,0},

		{1,1,1,
		1   ,1,
		1,0,1},

		//10
		{0,1,1,
		0,  1,
		0,1,1},

		{ 1,1,1,
		0,  1,
		0,1,1 },

		{ 0,1,1,
		0,  1,
		1,1,1 },

		{ 1,1,1,
		0,  1,
		1,1,1 },

		//11
		{1,1,0,
		1,  0,
		1,1,0},

		{ 1,1,1,
		1,  0,
		1,1,0 },

		{ 1,1,0,
		1,  0,
		1,1,1 },

		{ 1,1,1,
		1,  0,
		1,1,1 },


		//12-14
		{1,1,1,
		1,  1,
		1,1,1},

		//KULMA PALAT

	   //15
	   { 1,1,1,
	   1,  1,
	   1,1,0 },

		//16
		{ 1,1,1,
		1,  1,
		0,1,1 },

		//17
		{ 1,1,0,
		1,  1,
		1,1,1 },

		//18
		{0,1,1,
		1,  1,
		1,1,1},

		//19
		{0,0,0
		,0,  0,
		0,0,0},


		//Hassut piippu palat

		{0, 0, 0,
		0,    0,
		1, 1, 1},

		{ 1, 1, 1,
		0,    0,
		0, 0, 0 },

		{ 0, 0, 1,
		0,    1,
		0, 0, 1 },

		{ 1, 0, 0,
		1,    0,
		1, 0, 0 },

		{ 1, 1, 0,  // putken ala osa
		1,    1,
		1, 1, 0 },


		{ 0, 1, 1,
		1,    1,
		0, 1, 1 },

		{ 0, 1, 0,
		1,    1,
		1, 1, 1 },

		{ 1, 1, 1,
		1,    1,
		0, 1, 0 },
	};

};

