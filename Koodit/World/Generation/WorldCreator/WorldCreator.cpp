#include "WorldCreator.h"
#include <chrono>

//Checks if given cordinates are in a array.
bool WorldCreator::isInBounds(sf::Vector2i currentPosition, sf::Vector2i gridSize)
{
	return currentPosition.x > 0 && currentPosition.x < gridSize.x && currentPosition.y > 0 && currentPosition.y < gridSize.y;
}

//Create a quad for the vertex array by giving the vertex it's position and texture cordinate.
void WorldCreator::createQuad(sf::Vertex *quad, sf::Vector2f position, sf::Vector2i texCoord, sf::Vector2f tileSize)
{
	const float sizeInTexture = 16.f;

	quad[0].position = sf::Vector2f((float)position.y * tileSize.x, (float)position.x * tileSize.y);
	quad[1].position = sf::Vector2f(((float)position.y+1) * tileSize.x, (float)position.x * tileSize.y);
	quad[2].position = sf::Vector2f(((float)position.y + 1 ) * tileSize.x, ((float)position.x + 1) * tileSize.y);
	quad[3].position = sf::Vector2f((float)position.y * tileSize.x, ((float)position.x + 1) * tileSize.y);

	quad[0].texCoords = sf::Vector2f((float)texCoord.x * sizeInTexture, 0 * (float)texCoord.y);
	quad[1].texCoords = sf::Vector2f(((float)texCoord.x +1) * sizeInTexture, 0 * (float)texCoord.y);
	quad[2].texCoords = sf::Vector2f(((float)texCoord.x +1) * sizeInTexture,  (float)texCoord.y);
	quad[3].texCoords = sf::Vector2f((float)texCoord.x * sizeInTexture,  (float)texCoord.y);
}

void WorldCreator::removeSpace(std::string& text)
{
	text.erase(std::remove_if(text.begin(), text.end(), isspace), text.end());
}

sf::Vector2i WorldCreator::findTexCoord(bool* blocks, sf::Vector2i tileSize)
{
	return sf::Vector2i(19, 16);
	std::vector<int8_t> possibleOutComes;
	std::string output, bits;
	std::ifstream inputfile("Koodit/World/Generation/WorldCreator/MatrixThings.txt");
	bool exit = false;
	if (!inputfile.is_open())
	{
		std::cout << "Error opening file";
	}
	//int row = -1;
	while (std::getline(inputfile, bits))
	{
		//row += 1;
		
		if (bits.size() != 15) { continue; }
		for (int bit = 0; bit < 7; bit++)
		{
			if ((bool)bits[static_cast<std::basic_string<char, std::char_traits<char>, std::allocator<char>>::size_type>(bit) * 2] != blocks[bit]) { continue; }
			//Found the texture number!
			exit = true;
			break;

		}
		//std::cout << "\n\n";
		if (exit) { break; }
	}
	//std::cout << row << "\n";
	std::getline(inputfile, output);
	std::stringstream iss(output);
	if (output.size() == 0) { output = "6"; }
	for (std::string s;iss >> s;)
	{ 
		possibleOutComes.push_back(std::stoi(s));
	}
	possibleOutComes.push_back(std::stoi(output));

	
	inputfile.close();
	//std::cout <<"\n"<< output << "\n";
	uint16_t xValue = possibleOutComes[rand() % possibleOutComes.size()]; 
	//std::cout << xValue;
	//xValue = 5;
	//return sf::Vector2i(xValue % (320 / tileSize.x), xValue / (320 / tileSize.y));
	return sf::Vector2i(xValue, 16);
}

sf::Vector2i WorldCreator::getTexCoord(bool* blocks)
{
	std::vector<std::vector<bool>> possiblities
	{
		//  0
		{0,0,0,
		0, 1,
		0,1,1}, 

		{0,0,1, 
		0, 1, 
		0,1,1},

		{0,0,1,
		0, 1,
		1,1,1},

		// 1
		{0,0,0,
		1, 0,
		1,1,0},

		{1,0,0,
		1, 0,
		1,1,0},

		{1,0,0,
		1, 0,
		1,1,1},

		//2


	};
	switch (*blocks)
	{
	default:
		break;
	case 1:
		return sf::Vector2i(19, 0);
	}


	return sf::Vector2i();
}

//Create a detailed vertex array with every quad that has it's own texture.
WorldCreator::WorldCreator(sf::VertexArray& tileMap, sf::Vector2i gridSize, int seed, float threshold, sf::Vector2f tileSize)
{
	std::chrono::time_point<std::chrono::system_clock> start, end;
	start = std::chrono::system_clock::now();

	CaveGeneration blockMap(seed, threshold, gridSize);
	std::cout << gridSize.x;
	sf::Vector2i neighborCellPositons[8] = { {-1,-1}, {0,-1}, {1,-1}, {-1,0}, {1,0}, {-1,1}, {0,1}, {1,1} };
	for (int y = 0; y < gridSize.y; y++)
	{
		//std::cout << "\n";
		for (int x = 0; x < gridSize.x; x++)
		{
			//std::cout << blockMap.getCaveBlock(sf::Vector2i(x, y)) << " ";
			//BLOCK FINDING
			//muutetaan 8 bittistä inttiä sen biteillä. esittää samaa kuin listaa kahdeksasta paikasta.
			if (!blockMap.getCaveBlock(sf::Vector2i(x, y))) { continue; }
			bool neighborBlocks[8]{};
			for (int index = 0; index < 8; index++)
			{
				if (!this->isInBounds(sf::Vector2i(x, y) + neighborCellPositons[index], gridSize)) 
				{ 
					//neighborBlocks |= (1 << index);
					neighborBlocks[index] = true;
					
					continue; 
				}
				neighborBlocks[index] = blockMap.getCaveBlock(sf::Vector2i(x, y) + neighborCellPositons[index]);
				
			}
			//std::cout << x << "\n";
			//std::cout << (unsigned int)neighborBlocks << "\n ";
			sf::Vector2i texCoord = this->findTexCoord(neighborBlocks,sf::Vector2i((int)tileSize.x,(int)tileSize.y));
			sf::Vertex *quad = &tileMap[(x + (static_cast<size_t>(y) * gridSize.x))*4];
			this->createQuad(quad,sf::Vector2f((float)y, (float)x), texCoord, tileSize);
		}
	}

	end = std::chrono::system_clock::now();
	std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() << " [microsecs]" << std::endl;

}
