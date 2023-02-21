#pragma once
#include <string>


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

public:
	void render();
	void selectItem();
};