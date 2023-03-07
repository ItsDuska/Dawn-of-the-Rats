#pragma once
#include  <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Rect.hpp>

class EntityCollisionHandler
{
protected:
	bool blockCollisions(sf::FloatRect sprite, sf::Vector2f point);
	bool spriteCollisions(sf::FloatRect *firstSprite, sf::FloatRect *secondSprite);
	void collisionOutput(sf::FloatRect* firstSprite, sf::FloatRect* secondSprite);
};

/*
block collision toteutus ehkä?
Tarvitaan uus array jossa on current chunkin blockmap?
sit lasketaan pelaajan cordinaatit blockmappien cordinaatteihin. ja katsotaan onko siinä palikkaa.
jos on niin katsotaan onko pelaaja sen tekemän neliön sisällä eli luodaan uus rect joka kuvaa palikan kokoa

*/