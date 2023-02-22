#pragma once
#include <string>
#include <SFML/Graphics/Sprite.hpp>
#include "../../Utils/Assets/AssetManager.h"

// jokaisella raritylla on oma värinsä
enum Rarity
{
	UNRARE,
	NORMAL,
	RARE,
	EPIC,
	LEGENDARY
};

//Pikku ikkuna ponnahtaa kun hiiri laitetaan itemin kohdalle. Tämä kertoo sen statsit.
// enchant glintti? eli sit vois olla enchant table pelissä :D

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