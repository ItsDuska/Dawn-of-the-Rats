#pragma once
#include  <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <vector>
#include <cmath>

class EntityCollisionHandler
{
	bool isInBounds(sf::Vector2i currentPosition, sf::Vector2i gridSize);
	void checkCollisionSides(sf::Vector2f &veclocity);
	const sf::Vector2i neighborCellPositons[8] = { {-1,-1}, {-1,0}, {-1,1},    {0,-1}, {0,1},     {1,-1},  {1,0}, {1,1} };
protected:
	bool _onGround = false;

	void blockCollisions(sf::FloatRect entity, std::vector<std::vector<bool>> &blockMap,sf::Vector2f *velocity,sf::Vector2f tileSize,sf::Vector2i gridSize, sf::Vector2i chunkCoord);
	bool spriteCollisions(sf::FloatRect *firstSprite, sf::FloatRect *secondSprite);
	
};

/*
block collision toteutus ehkä?
Tarvitaan uus array jossa on current chunkin blockmap?
sit lasketaan pelaajan cordinaatit blockmappien cordinaatteihin. ja katsotaan onko siinä palikkaa.
jos on niin katsotaan onko pelaaja sen tekemän neliön sisällä eli luodaan uus rect joka kuvaa palikan kokoa

*/