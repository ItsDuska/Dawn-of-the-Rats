#include "ChunkBuilder.h"


//Checks if given cordinates are in a array.
bool ChunkBuilder::isInBounds(sf::Vector2i currentPosition, sf::Vector2i gridSize)
{
	return currentPosition.x > 0 && currentPosition.x < gridSize.x && currentPosition.y > 0 && currentPosition.y < gridSize.y;
}

//Create a quad for the vertex array by giving the vertex it's position and texture cordinate.
void ChunkBuilder::createQuad(sf::Vertex *quad, sf::Vector2f position, sf::Vector2f texCoord, sf::Vector2f tileSize)
{
	quad[0].position = sf::Vector2f( position.y *	   tileSize.x,  position.x *	  tileSize.y);
	quad[1].position = sf::Vector2f((position.y + 1) * tileSize.x,  position.x *	  tileSize.y);
	quad[2].position = sf::Vector2f((position.y + 1) * tileSize.x, (position.x + 1) * tileSize.y);
	quad[3].position = sf::Vector2f( position.y *	   tileSize.x, (position.x + 1) * tileSize.y);
	
	quad[0].texCoords = sf::Vector2f( texCoord.x *      this->TEX_SIZE,  texCoord.y *	   this->TEX_SIZE);
	quad[1].texCoords = sf::Vector2f((texCoord.x + 1) * this->TEX_SIZE,  texCoord.y *	   this->TEX_SIZE);
	quad[2].texCoords = sf::Vector2f((texCoord.x + 1) * this->TEX_SIZE, (texCoord.y + 1) * this->TEX_SIZE);
	quad[3].texCoords = sf::Vector2f( texCoord.x *		this->TEX_SIZE, (texCoord.y + 1) * this->TEX_SIZE);
}

/*
Chunk borderit vois korjata siten että generatataan 
cavessa yhden suurempi luola mutta piirretään vaan se yhden pienempi versio siitä

*/


ChunkBuilder::~ChunkBuilder()
{
}

ChunkBuilder::ChunkBuilder()
{
}

const std::vector<std::vector<bool>>& ChunkBuilder::getBlockMap()
{
	return this->blockMap->getCaveMap();
}
//Create a detailed vertex array with every quad that has it's own texture.
void ChunkBuilder::buildChunk(sf::VertexBuffer& buffer, sf::Vector2i gridSize, int seed, float threshold, sf::Vector2f tileSize, sf::Vector2i chunkCoord)
{
	std::chrono::time_point<std::chrono::system_clock> start, end;
	start = std::chrono::system_clock::now();

	
	std::unique_ptr<sf::Vertex[]> chunkVerticies = std::make_unique<sf::Vertex[]>(static_cast<size_t>(gridSize.y) * gridSize.x * 4);


	this->blockMap = std::make_unique<CaveGeneration>(seed, threshold, gridSize, chunkCoord);
	const sf::Vector2f WORLD_POSITION = { (float)((chunkCoord.x -1) * gridSize.x), (float)((chunkCoord.y - 1) * gridSize.y) };
	
	//vasen ylä -> alas
	for (int y = 1; y < gridSize.y+1; y++)
	{
		for (int x = 1; x < gridSize.x+1; x++)
		{
			//std::cout << blockMap.getCaveBlock(sf::Vector2i(x, y)) << " ";
			//BLOCK FINDING
			//muutetaan 8 bittistä inttiä sen biteillä. esittää samaa kuin listaa kahdeksasta paikasta.
			if (!blockMap->getCaveBlock(sf::Vector2i(x, y))) { continue; } // tähän arvo joka vaihdaa moden ruohon ja läpi mentävien kohdalle
			bool neighborBlocks[8]{};
			
			//int airBlockCounter = 0;

			for (int index = 0; index < 8; index++)
			{
				/*
				if (!this->isInBounds(sf::Vector2i(x, y) + neighborCellPositons[index], sf::Vector2i(gridSize.x+2, gridSize.y + 2)))
				{
					neighborBlocks[index] = true;
					std::cout << x + neighborCellPositons[index].x << "  " << y + neighborCellPositons[index].y << "\n";
					continue;
				}
				*/
				neighborBlocks[index] = blockMap->getCaveBlock(sf::Vector2i(x, y) + this->neighborBlockPositons[index]);

				//if (neighborBlocks[index] == 0)
				//{
					//airBlockCounter++;
				//}
			}

			//if (airBlockCounter == 8) 
			//{
				//continue;
			//}
			
			const sf::Vector2f texCoord = this->blockBuilder.getTexCoord(neighborBlocks);
			sf::Vertex* quad = &chunkVerticies.get()[(size_t(x-1) + (static_cast<size_t>(y-1) * gridSize.x)) * 4];
			const sf::Vector2f pos(WORLD_POSITION + sf::Vector2f((float)x-1, (float)y-1));

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
