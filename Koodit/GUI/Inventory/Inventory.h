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
	std::vector<std::unique_ptr<Item>> _items;
	sf::Sprite _inventoryBackground;
	std::string statsString; 
	sf::Vector2f _originalPosition;
	Text stats;
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
