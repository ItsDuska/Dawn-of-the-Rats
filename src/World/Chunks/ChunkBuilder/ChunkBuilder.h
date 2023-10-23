#pragma once
#include "World/Cave/CaveGenerator.h"
#include "Assets/Textures/AssetManager.h"
#include "World/Chunks/BlockTextureMapper/BlockTextureMapper.h"
#include <SFML/Graphics/VertexBuffer.hpp>
#include <SFML/Graphics/Vertex.hpp>
#include <memory>
#include <chrono>
#include <string>

//Constructs the tilemap for a Chunk.
class ChunkBuilder
{
private:
	void createQuad(sf::Vertex *quad,sf::Vector2f position, sf::Vector2f texCoord, sf::Vector2f tileSize);

	std::unique_ptr<CaveGeneration> blockMap;

	BlockTextureMapper blockBuilder;

	//const int texCoordTable[45];
	const float TEX_SIZE = 16.f;
	const sf::Vector2i neighborBlockPositons[8] = { {-1,-1}, {-1,0}, {-1,1},    {0,-1}, {0,1},     {1,-1},  {1,0}, {1,1} };

public:
	~ChunkBuilder();
	ChunkBuilder();
	const std::vector<std::vector<Block>> getBlockMap();
	void buildChunk(sf::VertexBuffer& buffer, sf::Vector2i gridSize, int seed, float threshold, sf::Vector2f tileSize, sf::Vector2i chunkCoord);
};

