#pragma once
#include "CaveGenerator.h"
#include <SFML/Graphics.hpp>
#include "../../../Utils/Assets/AssetManager.h"


//Constructs the tilemap
class WorldCreator
{
private:
	bool isInBounds(sf::Vector2i currentPosition,sf::Vector2i gridSize);
	void createQuad(sf::Vertex *quad,sf::Vector2i position, sf::Vector2i texCoord, sf::Vector2f tileSize);
	sf::Vector2f findTexCoord(sf::Vector2i position);
public:
	WorldCreator(sf::VertexArray &tileMap,sf::Vector2i gridSize, int seed, float threshold, sf::Vector2f tileSize);
};

