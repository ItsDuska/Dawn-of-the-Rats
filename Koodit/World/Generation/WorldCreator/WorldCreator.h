#pragma once
#include "CaveGenerator.h"
#include <SFML/Graphics.hpp>
#include "../../../Utils/Assets/AssetManager.h"
#include<fstream>
#include <string>
#include <sstream>

//Constructs the tilemap for a Chunk.
class WorldCreator
{
private:
	bool isInBounds(sf::Vector2i currentPosition,sf::Vector2i gridSize);
	void createQuad(sf::Vertex *quad,sf::Vector2f position, sf::Vector2i texCoord, sf::Vector2f tileSize);
	void removeSpace(std::string &text);
	sf::Vector2i findTexCoord(bool *blocks, sf::Vector2i tileSize);
	sf::Vector2i getTexCoord(bool* blocks);
public:
	WorldCreator(sf::VertexArray &tileMap,sf::Vector2i gridSize, int seed, float threshold, sf::Vector2f tileSize);
};

