#include "WorldCreator.h"


//Checks if given cordinates are in a array.
bool WorldCreator::isInBounds(sf::Vector2i currentPosition, sf::Vector2i gridSize)
{
	return currentPosition.x > 0 && currentPosition.x < gridSize.x && currentPosition.y > 0 && currentPosition.y < gridSize.y;
}
//
//Create a quad for the vertex array by giving the vertex it's position and texture cordinate.
void WorldCreator::createQuad(sf::Vertex *quad, sf::Vector2f position, sf::Vector2i texCoord, sf::Vector2f tileSize)
{
	quad[0].position = sf::Vector2f((float)position.x * tileSize.x, (float)position.y * tileSize.y);
	quad[1].position = sf::Vector2f(((float)position.x+1) * tileSize.x, (float)position.y * tileSize.y);
	quad[2].position = sf::Vector2f(((float)position.x + 1 ) * tileSize.x, ((float)position.y + 1) * tileSize.y);
	quad[3].position = sf::Vector2f((float)position.x * tileSize.x, ((float)position.y + 1) * tileSize.y);

	quad[0].texCoords = sf::Vector2f(texCoord.x * tileSize.x, texCoord.y * tileSize.y);
	quad[1].texCoords = sf::Vector2f((texCoord.x + 1) * tileSize.x, texCoord.y * tileSize.y);
	quad[2].texCoords = sf::Vector2f((texCoord.x + 1) * tileSize.x, (texCoord.y + 1) * tileSize.y);
	quad[3].texCoords = sf::Vector2f(texCoord.x * tileSize.x, (texCoord.y + 1) * tileSize.y);
}

void WorldCreator::removeSpace(std::string& text)
{
	text.erase(std::remove_if(text.begin(), text.end(), isspace), text.end());
}

sf::Vector2i WorldCreator::findTexCoord(int8_t blocks, sf::Vector2i tileSize)
{
	const int16_t FILE_ROWS = 512;
	std::vector<int8_t> possibleOutComes;
	std::string output;
	std::ifstream inputfile("Koodit/World/Generation/WorldCreator/MatrixThings.txt");
	std::string bits;
	if (!inputfile.is_open())
		std::cout << "Error opening file";
	while (std::getline(inputfile, bits))
	{
		int8_t bitOption;
		this->removeSpace(bits);
		bitOption = (std::stoi(bits));
		if (bitOption != blocks) { continue; }
		std::getline(inputfile, output);
		std::stringstream iss(output);
		for (std::string s;iss >> s;) {possibleOutComes.push_back(std::stoi(s)); }
		possibleOutComes.push_back(std::stoi(output));
		break;
	}
	inputfile.close();
	const int8_t xValue = possibleOutComes[rand() % possibleOutComes.size()]; 
	return sf::Vector2i(xValue * tileSize.x,0);
}

//Create a detailed vertex array with every quad that has it's own texture.
WorldCreator::WorldCreator(sf::VertexArray& tileMap, sf::Vector2i gridSize, int seed, float threshold, sf::Vector2f tileSize)
{
	CaveGeneration blockMap(seed, threshold, gridSize);
	sf::Vector2i neighborCellPositons[8] = { {-1,-1}, {0,-1}, {1,-1}, {-1,0}, {1,0}, {-1,1}, {0,1}, {1,1} };
	for (int y = 0; y < gridSize.y; y++)
	{
		for (int x = 0; x < gridSize.x; x++)
		{
			//BLOCK FINDING
			//muutetaan 8 bittistä inttiä sen biteillä. esittää samaa kuin listaa kahdeksasta paikasta.
			if (blockMap.getCaveBlock(sf::Vector2i(x, y))) { continue; }
			int8_t neighborBlocks = 0;
			for (int index = 0; index < 8; index++)
			{
				if (!this->isInBounds(sf::Vector2i(x, y) + neighborCellPositons[index], gridSize)) 
				{ 
					neighborBlocks |= (1u << index);
					continue; 
				}
				bool block = blockMap.getCaveBlock(sf::Vector2i(x,y) + neighborCellPositons[index]);
				neighborBlocks |= (1 << index)& (~((1 << index) ^ (block << index)));
			}
			sf::Vector2i texCoord = this->findTexCoord(neighborBlocks,sf::Vector2i((int)tileSize.x,(int)tileSize.y));
			sf::Vertex *quad = &tileMap[(y + static_cast<size_t>(x) * gridSize.x)*4];
			this->createQuad(quad,sf::Vector2f(x, y), texCoord, tileSize);
		}
	}
}
