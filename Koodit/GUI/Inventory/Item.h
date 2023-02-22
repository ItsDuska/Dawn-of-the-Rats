#pragma once
#include <string>
#include <SFML/Graphics/Sprite.hpp>
#include "../../Utils/Assets/AssetManager.h"

// jokaisella raritylla on oma v�rins�
enum Rarity
{
	UNRARE,
	NORMAL,
	RARE,
	EPIC,
	LEGENDARY
};

//Pikku ikkuna ponnahtaa kun hiiri laitetaan itemin kohdalle. T�m� kertoo sen statsit.
// enchant glintti? eli sit vois olla enchant table peliss� :D

class Item
{
private:
	std::string _itemName;
	Rarity rarity;
	sf::Sprite itemSprite;

public:
	void render();
	void selectItem();
};