#pragma once
#include "System/ECS/Systems/System.h"
#include "System/ECS/Coordinator/Cordinator.h"
#include "World/Generation/Chunks/Chunk/Chunk.h"
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
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

	void blockCollision(
		Coordinator& entityManager, 
		const std::unique_ptr<Chunk> &chunks,
		Component::Transform& transform,
		const ChunkSettings& chunkSettings,
		sf::Vector2i entityPositionInChunk,
		Component::Hitbox hitbox, Component::RigidBody& rigidbody, bool &onGround
	);

	void entityCollision(Coordinator& entityManager);

	void render(sf::RenderTarget* window);

	CollisionSystem();
private:
	bool inBounds(sf::Vector2i pos, sf::Vector2i bounds);
	bool collide(sf::FloatRect entity, sf::FloatRect block);
	int getChunkIndex(std::vector<sf::Vector2i> list, sf::Vector2i position);
	void horizontalCollision(Component::Transform &transform,Component::RigidBody &rigidBody,sf::Vector2f collisionPosition, sf::Vector2f tileSize, const Component::Hitbox &hitbox);
	bool verticalCollision(Component::Transform &transform, Component::RigidBody &rigidBody, sf::Vector2f collisionPosition, sf::Vector2f tileSize, const Component::Hitbox &hitbox, bool& onGround);

	bool colliding;
	bool hasCollidedHorizontaly = false;
	bool hasCollidedVerticly = false;
	sf::RectangleShape palikka[8];
	const sf::Vector2i neighborBlockPositons[8] = { {-1,-1}, {-1,0}, {-1,1},    {0,-1}, {0,1},     {1,-1},  {1,0}, {1,1} };
};

