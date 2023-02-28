#pragma once
#include "Item.h"
#include <vector>
#include <sstream>
#include <memory>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Window/Mouse.hpp>
#include "../../Player/PlayerStats.h"
#include "../../Visuals/Texts/Text.h"

class Inventory
{
private:
	//window size eli inventory ikkunan koko
	

	//inventory on  10*16, 9*16
	//Miinustetaan inventorin koosta sen reunat ja sitten saada sen pos

	//Jokaisen inventory slotin sijainti
	std::vector<std::unique_ptr<Item>> _items;
	Text stats;
	sf::Sprite _inventoryBackground;
	//Tarvitaan pelaaja classista sen statseja. ehk‰ niille oma class jota voidaan k‰ytt‰‰. 
	//sit pelaajassa voidaan heitt‰ siit‰ classista refrens eli * merkill‰.
	std::string statsString; 
	sf::Vector2f _originalPosition;
	int _selectedItemIndex;
	bool isSelceted;

	void deleteItem();
	void placeItem();
	void selectItem();
	bool hasClicked();
	bool checkNewPosition();
	void showItemStats(int itemIndex); // n‰ytt‰‰ pienen ikkunan jossa n‰kyy itemin statsit
	sf::Vector2i getNewPositionIndex();
public:
	bool showInventory = false;
	void updateStatText(PlayerStats *stats);
	Inventory(sf::Vector2f windowSize, PlayerStats& stats);
	void addNewItem();
	void update();
	void render(sf::RenderTarget *window);

};
