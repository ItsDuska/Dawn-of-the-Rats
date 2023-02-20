#pragma once
#include "Item.h"
#include <vector>

class Inventory
{
private:
	//window size eli inventory ikkunan koko
	
	//Jokaisen inventory slotin sijainti
	std::vector<Item> Items;

	//Tarvitaan pelaaja classista sen statseja. ehk‰ niille oma class jota voidaan k‰ytt‰‰. 
	//sit pelaajassa voidaan heitt‰ siit‰ classista refrens eli * merkill‰.

	void showItemStats(); // n‰ytt‰‰ pienen ikkunan jossa n‰kyy itemin statsit
public:
	void update();
	void render();

};
