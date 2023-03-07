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
block collision toteutus ehk�?
Tarvitaan uus array jossa on current chunkin blockmap?
sit lasketaan pelaajan cordinaatit blockmappien cordinaatteihin. ja katsotaan onko siin� palikkaa.
jos on niin katsotaan onko pelaaja sen tekem�n neli�n sis�ll� eli luodaan uus rect joka kuvaa palikan kokoa

*/