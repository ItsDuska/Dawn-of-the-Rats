#pragma once
#include "Item.h"
#include <vector>
#include <sstream>
#include <memory>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Window/Mouse.hpp>
#include "../../Player/PlayerStats.h"
#include "Assets/Texts/Text.h"
#include "System/ECS/Components/Components.h"

namespace GUI
{
	class Inventory
	{
	private:
		std::vector<std::unique_ptr<Item>> _items;
		sf::Sprite _inventoryBackground;
		std::string statsString; 
		sf::Vector2f _originalPosition;
		engine::Text stats;
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
		//bool showInventory = false;
		//void updateStatText(Component::Healt health, Component::Mana mana, Component::Speed speed,
			//Component::Damage damage, Component::Defence defence, Component::Luck luck);
		Inventory(sf::Vector2f windowSize);
		void addNewItem();
		void update();
		void render(sf::RenderTarget *window);

	};
}