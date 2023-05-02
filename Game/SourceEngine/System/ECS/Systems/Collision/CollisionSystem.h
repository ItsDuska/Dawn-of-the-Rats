#pragma once
#include "System/ECS/Systems/System.h"
#include "System/ECS/Coordinator/Cordinator.h"
#include "World/Generation/Chunks/Chunk/Chunk.h"
#include <cmath>


class CollisionSystem : public System
{
public:
	void update(
		Coordinator& entityManager,
		const std::vector<std::unique_ptr<Chunk>>* chunks,
		const ChunkSettings& chunkSettings,
		const std::vector<sf::Vector2i>& chunkCords
	);

	bool blockCollision(
		Coordinator& entityManager, 
		const std::unique_ptr<Chunk> &chunks,
		Component::Transform transform,
		const ChunkSettings& chunkSettings,
		sf::Vector2i entityPositionInChunk,
		sf::Vector2f hitbox
	);

	bool entityCollision(Coordinator& entityManager);

private:
	bool inBounds(sf::Vector2i pos, sf::Vector2i bounds);
	bool collide(sf::FloatRect entity, sf::FloatRect block);
	int getChunkIndex(std::vector<sf::Vector2i> list, sf::Vector2i position);

	const sf::Vector2i neighborBlockPositons[8] = { {-1,-1}, {-1,0}, {-1,1},    {0,-1}, {0,1},     {1,-1},  {1,0}, {1,1} };
};

