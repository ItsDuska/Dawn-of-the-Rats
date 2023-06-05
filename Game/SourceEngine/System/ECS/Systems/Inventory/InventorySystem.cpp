#include "InventorySystem.h"

std::string InventorySystem::roundTwo(const float x) {
	std::stringstream ss;
	ss << std::fixed;
	ss.precision(2);
	ss << x;
	return ss.str();
}

InventorySystem::InventorySystem()
{
	AssetManager::loadTexture("Inventory", "NewSprites/Inventory.png");
	AssetManager::loadTexture("InventoryItems", "NewSprites/GUI_ITEM_SPRITES.png");
	this->background.setTexture(AssetManager::getTexture("Inventory"));

	const sf::Vector2f spriteSize = {
			background.getGlobalBounds().width,
			background.getGlobalBounds().height
	};

	background.setOrigin(spriteSize.x / 2.f, spriteSize.y / 2.f);
	background.setPosition(
		sf::VideoMode::getDesktopMode().width / 2.f,
		sf::VideoMode::getDesktopMode().height / 2.f
	);

	background.scale(
		std::round((sf::VideoMode::getDesktopMode().height / spriteSize.y) - 2.f),
		std::round((sf::VideoMode::getDesktopMode().height / spriteSize.y) - 2.f)
	);

	stats.setText(30, "TempText",
		sf::Vector2f(sf::VideoMode::getDesktopMode().width / 2.25f,
			background.getPosition().y / 2.f)
	);
	


}

void InventorySystem::addNewItem(Coordinator& entityManager)
{
	for (auto& entity : this->mEntities)
	{
		auto& inventory = entityManager.getComponent <Component::Inventory>(entity);
		inventory._items.push_back(std::make_shared<Item>("InventoryItems",
			sf::IntRect(48, 16, 16, 16), this->background.getGlobalBounds()));
	}
}

void InventorySystem::update(Coordinator& entityManager)
{
	for (auto& entity : this->mEntities)
	{
		auto& inventory = entityManager.getComponent <Component::Inventory>(entity);

		if (!inventory.showInventory) { return; }

		const auto& health = entityManager.getComponent <Component::Health>(entity);
		const auto& mana = entityManager.getComponent <Component::Mana>(entity);
		const auto& damage = entityManager.getComponent <Component::Damage>(entity);
		const auto& defence = entityManager.getComponent <Component::Defence>(entity);
		const auto& speed = entityManager.getComponent <Component::Speed>(entity);
		const auto& luck = entityManager.getComponent <Component::Luck>(entity);

		if (inventory.updateText)
		{
			inventory.statsString = "Max Healt : " + std::to_string(health.maxHealt)
				+ "\nCurrent Healt : " + std::to_string(health.currentHealt)
				+ "\nHealt Regeneration : " + std::to_string(health.healtRegen)
				+ "\nMax Mana : " + std::to_string(mana.maxMana)
				+ "\nCurrent Mana : " + std::to_string(mana.currentMana)
				+ "\nMana Regeneration : " + std::to_string(mana.manaRegen)
				+ "\nMelee Damage : " + std::to_string(damage.meleeDamage)
				+ "\nMagic Damage : " + std::to_string(damage.magicDamage)
				+ "\nMelee Defense : " + std::to_string(defence.meleeDefence)
				+ "\nMagic Defense : " + std::to_string(defence.magicDefence)
				+ "\nSpeed : " + roundTwo(speed.speed)
				+ "\nLuck : " + std::to_string(luck.luck);
			stats.changeString(inventory.statsString);
			inventory.updateText = false;
		}
		
		if (!this->hasClicked())
		{
			if (inventory.isSelceted)
			{
				this->placeItem(inventory);
			}

			return;
		}

		if (inventory.isSelceted)
		{
			inventory._items[inventory._selectedItemIndex]
				.get()->setPosition(sf::Vector2f((float)sf::Mouse::getPosition().x,
				(float)sf::Mouse::getPosition().y - inventory._items[inventory._selectedItemIndex]
				.get()->getRect().height / 2.f));
		}
		else
		{
			this->selectItem(inventory);
		}
	}
}

void InventorySystem::render(Coordinator& entityManager, sf::RenderTarget* window)
{
	for (auto& entity : this->mEntities)
	{
		auto& inventory = entityManager.getComponent <Component::Inventory>(entity);
		if (!inventory.showInventory) { return; }

		window->draw(this->background);
		window->draw(stats.getText());

		for (auto& item : inventory._items)
		{
			item.get()->render(window);
		}
	}
}

void InventorySystem::deleteItem()
{
}

void InventorySystem::placeItem(Component::Inventory& inventory)
{
	sf::Vector2f bounds(this->background.getGlobalBounds().width, this->background.getGlobalBounds().height);

	if (this->checkNewPosition(bounds))
	{
		inventory._items[inventory._selectedItemIndex].get()->setPositionOnGrid(this->getNewPositionIndex(bounds));
	}
	else
	{
		inventory._items[inventory._selectedItemIndex].get()->setPosition(inventory._originalPosition);
	}

	inventory.isSelceted = false;
}

void InventorySystem::selectItem(Component::Inventory& inventory)
{
	for (int index = 0; index < inventory._items.size(); index++)
	{
		if (inventory._items[index].get()->getRect().contains((sf::Vector2f)sf::Mouse::getPosition()))
		{
			inventory._selectedItemIndex = index;
			inventory._originalPosition = inventory._items[index].get()->getPosition();
			inventory.isSelceted = true;
			return;
		}
	}
}

bool InventorySystem::hasClicked()
{
	return sf::Mouse::isButtonPressed(sf::Mouse::Left);
}

bool InventorySystem::checkNewPosition(sf::Vector2f backgroundGlobalBounds)
{
	sf::Vector2i newPos = this->getNewPositionIndex(backgroundGlobalBounds);
	return ((newPos.x == 2 || newPos.x == 9) && (newPos.y >= 0 && newPos.y <= 6));
}

void InventorySystem::showItemStats(int itemIndex)
{
}

sf::Vector2i InventorySystem::getNewPositionIndex(sf::Vector2f backgroundGlobalBounds)
{
	sf::Vector2f blockSize(backgroundGlobalBounds.x / 10.f,
		backgroundGlobalBounds.y / 9.f);

	sf::Vector2i newPos = { (int)(std::floorf((float)sf::Mouse::getPosition().x / blockSize.x)) - 4,
		(int)(std::floorf((float)sf::Mouse::getPosition().y / blockSize.y)) - 2 };

	return newPos;
}
