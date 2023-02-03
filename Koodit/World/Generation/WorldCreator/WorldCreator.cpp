#include "WorldCreator.h"



bool WorldCreator::isInBounds(sf::Vector2i currentPosition, sf::Vector2i gridSize)
{
	return currentPosition.x > 0 && currentPosition.x < gridSize.x && currentPosition.y > 0 && currentPosition.y < gridSize.y;
}

void WorldCreator::createQuad(sf::Vertex *quad,sf::Vector2i position, sf::Vector2i texCoord,sf::Vector2f tileSize)
{
	quad[0].position = sf::Vector2f(position.x * tileSize.x, position.y * tileSize.y);
	quad[1].position = sf::Vector2f((position.x+1) * tileSize.x, position.y * tileSize.y);
	quad[2].position = sf::Vector2f((position.x + 1 ) * tileSize.x, (position.y + 1) * tileSize.y);
	quad[3].position = sf::Vector2f(position.x * tileSize.x, (position.y + 1) * tileSize.y);

	quad[0].texCoords = sf::Vector2f(texCoord.x * tileSize.x, texCoord.y * tileSize.y);
	quad[1].texCoords = sf::Vector2f((texCoord.x + 1) * tileSize.x, texCoord.y * tileSize.y);
	quad[2].texCoords = sf::Vector2f((texCoord.x + 1) * tileSize.x, (texCoord.y + 1) * tileSize.y);
	quad[3].texCoords = sf::Vector2f(texCoord.x * tileSize.x, (texCoord.y + 1) * tileSize.y);
}

sf::Vector2f WorldCreator::findTexCoord(sf::Vector2i position)
{

	return sf::Vector2f();
}

WorldCreator::WorldCreator(sf::VertexArray& tileMap, sf::Vector2i gridSize, int seed, float threshold, sf::Vector2f tileSize)
{
	CaveGeneration blockMap(seed, threshold, gridSize);
	sf::Vector2i neighborCells[8] = { {-1,-1},{0,-1},{1,-1},{-1,0},{1,0},{-1,1},{0,1},{1,1} };

	for (int y = 0; y < gridSize.y; y++)
	{
		for (int x = 0; x < gridSize.x; x++)
		{
			//BLOCK FINDING
			for (sf::Vector2i neighbor : neighborCells)
			{
				if (!this->isInBounds(sf::Vector2i(x, y) + neighbor, gridSize)) { continue; }
				//Pitää käydä joka ikinen muodostelma läpi jotta saadaan selville mikä palikka tulee siihen eli onko se kulma palikka vai ei
				// Samaa hommaa joudutaan tekeen miten mc:n cräftin systeemi checkkaa reseptin.
				// atm laiskuus joten yks palikka vaa
				this->createQuad(&tileMap[y + static_cast<size_t>(x) * gridSize.x], sf::Vector2i(x, y), sf::Vector2i(0, 0), tileSize);
			}
			
		}
	}

}
