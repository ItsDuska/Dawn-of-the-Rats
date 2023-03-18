#include "ChunkBuilder.h"


//Checks if given cordinates are in a array.
bool ChunkBuilder::isInBounds(sf::Vector2i currentPosition, sf::Vector2i gridSize)
{
	return currentPosition.x > 0 && currentPosition.x < gridSize.x && currentPosition.y > 0 && currentPosition.y < gridSize.y;
}

//Create a quad for the vertex array by giving the vertex it's position and texture cordinate.
void ChunkBuilder::createQuad(sf::Vertex *quad, sf::Vector2f position, sf::Vector2i texCoord, sf::Vector2f tileSize)
{
	const float sizeInTexture = 16.f;

	quad[0].position = sf::Vector2f(position.y * tileSize.x, position.x * tileSize.y);
	quad[1].position = sf::Vector2f((position.y+1) * tileSize.x, position.x * tileSize.y);
	quad[2].position = sf::Vector2f((position.y + 1 ) * tileSize.x, (position.x + 1) * tileSize.y);
	quad[3].position = sf::Vector2f(position.y * tileSize.x, (position.x + 1) * tileSize.y);
	
	quad[0].texCoords = sf::Vector2f((float)texCoord.x * sizeInTexture, 0 * (float)texCoord.y);
	quad[1].texCoords = sf::Vector2f(((float)texCoord.x +1) * sizeInTexture, 0 * (float)texCoord.y);
	quad[2].texCoords = sf::Vector2f(((float)texCoord.x +1) * sizeInTexture,  (float)texCoord.y);
	quad[3].texCoords = sf::Vector2f((float)texCoord.x * sizeInTexture,  (float)texCoord.y);
}

void ChunkBuilder::removeSpace(std::string& text)
{
	text.erase(std::remove_if(text.begin(), text.end(), isspace), text.end());
}

/*
Chunk borderit vois korjata siten että generatataan 
cavessa yhden suurempi luola mutta piirretään vaan se yhden pienempi versio siitä

*/

sf::Vector2i ChunkBuilder::getTexCoord(bool* blocks)
{
	int index = 0;
	const std::vector<std::vector<bool>> possiblities
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
		0,0,0}
	};

	for (int i = 0; i < possiblities.size(); i++)
	{
		bool isSame = false;

		for (int bit = 0; bit < 8; bit++)
		{
			if (blocks[bit] != possiblities[i][bit])
			{
				isSame = false;
				break;
			}
			isSame = true;
		}
		if (isSame) { index = i; break; }
	}

	if (index == 32) { index = 12; } //T
	else if (index >= 0 && index <= 3) { index = 0; } //k1
	else if (index >= 4 && index <= 7) { index = 1; } //k2
	else if (index >= 8 && index <= 11) { index = 2; } //k3
	else if (index >= 12 && index <= 15) { index = 3; } //k4
	else if (index >= 16 && index <= 19) { index = 4;} //SN
	else if (index >= 20 && index <= 23) { index = 7; } //SS
	else if (index >= 24 && index <= 27) { index = 9; } //SW
	else if (index >= 28 && index <= 31) { index = 11; } //SE
	else if (index == 33) { index = 14; } //L1
	else if (index == 34) { index = 15; } //L2
	else if (index == 35) { index = 16; } //L3
	else if (index == 36) { index = 17; } //L4
	else { index = 19; } // O
	
	return sf::Vector2i(index,16);
}

ChunkBuilder::~ChunkBuilder()
{
}

const std::vector<std::vector<bool>> ChunkBuilder::getBlockMap()
{
	return this->blockMap.get()->getCaveMap();
}
//Create a detailed vertex array with every quad that has it's own texture.
void ChunkBuilder::buildChunk(sf::VertexBuffer& buffer, sf::Vector2i gridSize, int seed, float threshold, sf::Vector2f tileSize, sf::Vector2i chunkCoord)
{
	std::chrono::time_point<std::chrono::system_clock> start, end;
	start = std::chrono::system_clock::now();

	
	std::unique_ptr<sf::Vertex[]> chunkVerticies = std::make_unique<sf::Vertex[]>(static_cast<size_t>(gridSize.y) * gridSize.x * 4);


	blockMap = std::make_unique<CaveGeneration>(seed, threshold, gridSize, chunkCoord);
	const sf::Vector2f WORLD_POSITION = { (float)((chunkCoord.x - 1) * gridSize.x), (float)((chunkCoord.y - 1) * gridSize.y) };
	const sf::Vector2i neighborCellPositons[8] = { {-1,-1}, {-1,0}, {-1,1},    {0,-1}, {0,1},     {1,-1},  {1,0}, {1,1} };
	//vasen ylä -> alas
	for (int y = 0; y < gridSize.y; y++)
	{
		for (int x = 0; x < gridSize.x; x++)
		{
			//std::cout << blockMap.getCaveBlock(sf::Vector2i(x, y)) << " ";
			//BLOCK FINDING
			//muutetaan 8 bittistä inttiä sen biteillä. esittää samaa kuin listaa kahdeksasta paikasta.
			if (!blockMap.get()->getCaveBlock(sf::Vector2i(x, y))) { continue; } // tähän arvo joka vaihdaa moden ruohon ja läpi mentävien kohdalle
			bool neighborBlocks[8]{};

			int airBlockCounter = 0;

			for (int index = 0; index < 8; index++)
			{
				if (!this->isInBounds(sf::Vector2i(x, y) + neighborCellPositons[index], gridSize))
				{
					neighborBlocks[index] = true;
					continue;
				}

				neighborBlocks[index] = blockMap.get()->getCaveBlock(sf::Vector2i(x, y) + neighborCellPositons[index]);

				if (neighborBlocks[index] == 0)
				{
					airBlockCounter++;
				}
			}

			if (airBlockCounter == 8) { continue; }

			const sf::Vector2i texCoord = this->getTexCoord(neighborBlocks);
			sf::Vertex* quad = &chunkVerticies.get()[(x + (static_cast<size_t>(y) * gridSize.x)) * 4];
			const sf::Vector2f pos(WORLD_POSITION + sf::Vector2f((float)x, (float)y));

			this->createQuad(quad, pos, texCoord, tileSize);
		}
	}

	/*
	Ruoho palikat voitaisinn vetää myös samalla vertex arraylla,
	mutta collisionissa katsottaisiin myös
	jokaisen texCoord jas sen perusteella pääteellää collidetaanko vai ei
	*/
	buffer.update(chunkVerticies.get());
	end = std::chrono::system_clock::now();
	std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() << " [microsecs]" << std::endl;
}
