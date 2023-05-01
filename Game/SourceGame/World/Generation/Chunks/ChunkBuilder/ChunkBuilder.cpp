#include "ChunkBuilder.h"


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
Chunk borderit vois korjata siten ett‰ generatataan 
cavessa yhden suurempi luola mutta piirret‰‰n vaan se yhden pienempi versio siit‰

*/


ChunkBuilder::~ChunkBuilder()
{
}

ChunkBuilder::ChunkBuilder()
{
}

const std::vector<std::vector<Block>>& ChunkBuilder::getBlockMap()
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
	
	//vasen yl‰ -> alas
	for (int y = 1; y < gridSize.y+1; y++)
	{
		for (int x = 1; x < gridSize.x+1; x++)
		{
			if (!blockMap->getCaveBlock(sf::Vector2i(x, y)).isBlock) 
			{
				blockMap->getCaveBlock(sf::Vector2i(x, y)).isSolid = false; // t‰h‰n arvo joka vaihdaa moden ruohon ja l‰pi ment‰vien kohdalle
			} 
			else
			{
				blockMap->getCaveBlock(sf::Vector2i(x, y)).isSolid = true;
			}
			
			bool neighborBlocks[8]{};
			int airBlocks = 0;

			for (int index = 0; index < 8; index++)
			{
				neighborBlocks[index] = blockMap->getCaveBlock(sf::Vector2i(x, y) + this->neighborBlockPositons[index]).isBlock;
				if (!neighborBlocks[index])
				{
					airBlocks++;
				}
			}

			if (airBlocks == 8)
			{
				continue;
			}

			sf::Vector2f texCoord;

			if (!blockMap->getCaveBlock(sf::Vector2i(x, y)).isSolid)
			{
				if (!neighborBlocks[1] && !neighborBlocks[3] && !neighborBlocks[4] && !neighborBlocks[6])
				{
					continue;
				}
				std::cout << "\n HEI OLEN ELOSSA!!!!! \n";
				bool neighborBlocksGrass[4] = { neighborBlocks[1],neighborBlocks[3],neighborBlocks[4],neighborBlocks[6] };
				texCoord = this->blockBuilder.getGrassTexCoord(neighborBlocksGrass);
			}
			else
			{
				texCoord = this->blockBuilder.getTexCoord(neighborBlocks);
			}
			
			sf::Vertex* quad = &chunkVerticies.get()[(size_t(x-1) + (static_cast<size_t>(y-1) * gridSize.x)) * 4];
			const sf::Vector2f pos(WORLD_POSITION + sf::Vector2f((float)x-1, (float)y-1));

			this->createQuad(quad, pos, texCoord, tileSize);
		}
	}

	buffer.update(chunkVerticies.get());
	end = std::chrono::system_clock::now();
	std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() << " [microsecs]" << std::endl;
}
