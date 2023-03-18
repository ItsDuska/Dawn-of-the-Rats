#pragma once
#include "../../Cave/CaveGenerator.h"
#include <SFML/Graphics.hpp>
#include "Assets/Textures/AssetManager.h"
#include<fstream>
#include <string>
#include <sstream>
#include <SFML/Graphics/VertexBuffer.hpp>
#include <memory>
#include <chrono>

//Constructs the tilemap for a Chunk.
class ChunkBuilder
{
private:
	bool isInBounds(sf::Vector2i currentPosition,sf::Vector2i gridSize);
	void createQuad(sf::Vertex *quad,sf::Vector2f position, sf::Vector2i texCoord, sf::Vector2f tileSize);
	void removeSpace(std::string &text);

	sf::Vector2i getTexCoord(bool* blocks);
	std::unique_ptr<CaveGeneration> blockMap;
public:
	~ChunkBuilder();
	const std::vector<std::vector<bool>> getBlockMap();
	void buildChunk(sf::VertexBuffer& buffer, sf::Vector2i gridSize, int seed, float threshold, sf::Vector2f tileSize, sf::Vector2i chunkCoord);
};

