#pragma once
#include <string>
#include <cmath>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include "Assets/Textures/AssetManager.h"

enum class Type
{
	KEY,
	STAFF,
	RING,
	NECKLACE,
	BRACELET,
	MAGIC_TYPE,
	NONE
};


enum class Rarity
{
	COMMON,
	UNCOMMON,
	STRANGE,
	ARCANE,
	DIVINE
};
//Pikku ikkuna ponnahtaa kun hiiri laitetaan itemin kohdalle. Tämä kertoo sen statsit.
// enchant glintti? eli sit vois olla enchant table pelissä :D

class Item
{
private:
	Type _type;
	std::string _itemName;
	Rarity _rarity;
	sf::Sprite _itemSprite;
	sf::FloatRect SpritePositions;
public:
	Item(const std::string spriteName, const sf::IntRect itemArea, sf::FloatRect spriteSize);
	std::string getName();
	Rarity getRarity();
	sf::Sprite getSprite();
	sf::FloatRect getRect();
	sf::Vector2f getPosition();
	void setPositionOnGrid(sf::Vector2i indexPos);
	void setPosition(sf::Vector2f newPos);
	void setTexture(const std::string spriteName, const sf::IntRect itemArea, sf::FloatRect spriteSize);
	void render(sf::RenderTarget *window);
};