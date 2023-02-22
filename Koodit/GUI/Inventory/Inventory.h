#pragma once
#include "Item.h"
#include <vector>
#include <sstream>
#include <SFML/Graphics/RenderTarget.hpp>
#include "../../Player/PlayerStats.h"
#include "../../Visuals/Texts/Text.h"

class Inventory
{
private:
	//window size eli inventory ikkunan koko
	
	//Jokaisen inventory slotin sijainti
	std::vector<Item> _items;
	Text stats;
	sf::Sprite _inventoryBackground;
	//Tarvitaan pelaaja classista sen statseja. ehk‰ niille oma class jota voidaan k‰ytt‰‰. 
	//sit pelaajassa voidaan heitt‰ siit‰ classista refrens eli * merkill‰.
	std::string statsString; 


	
	void placeItem();
	void selectItem();
	bool hasClicked();
	void showItemStats(); // n‰ytt‰‰ pienen ikkunan jossa n‰kyy itemin statsit
public:
	void updateStatText(PlayerStats *stats);
	Inventory(sf::Vector2f windowSize, PlayerStats& stats);
	bool showInventory = false;
	void update();
	void render(sf::RenderTarget *window);

};
