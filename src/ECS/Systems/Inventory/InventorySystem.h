#pragma once
#include "ECS/Systems/System.h"
#include "ECS/Coordinator/Cordinator.h"
#include "GUI/Inventory/Item.h"
#include <SFML/Window/Mouse.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <sstream>

class InventorySystem : public System
{
public:
	void init(AssetManager& assetManager);
	void addNewItem(Coordinator& entityManager, AssetManager& assetManager);
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