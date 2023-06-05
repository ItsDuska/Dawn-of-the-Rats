#pragma once

#include <sstream>
#include "System/ECS/Systems/System.h"
#include "System/ECS/Coordinator/Cordinator.h"
#include "GUI/Inventory/Item.h"
#include <SFML/Window/Mouse.hpp>
#include <SFML/Window/VideoMode.hpp>

class InventorySystem : public System
{
public:
	InventorySystem();
	void addNewItem(Coordinator& entityManager);
	void update(Coordinator& entityManager);
	void render(Coordinator& entityManager, sf::RenderTarget* window);
private:
	void deleteItem();
	void placeItem(Component::Inventory& inventory);
	void selectItem(Component::Inventory& inventory);
	bool hasClicked();
	std::string roundTwo(const float x);
	bool checkNewPosition(sf::Vector2f backgroundGlobalBounds);
	void showItemStats(int itemIndex); // n‰ytt‰‰ pienen ikkunan jossa n‰kyy itemin statsit
	sf::Vector2i getNewPositionIndex(sf::Vector2f backgroundGlobalBounds);
	sf::Sprite background;
	engine::Text stats;
};