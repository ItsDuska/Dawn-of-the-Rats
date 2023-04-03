#include "Inventory.h"

std::string roundTwo(const float x) {
	std::stringstream ss;
	ss << std::fixed;
	ss.precision(2);
	ss << x;
	return ss.str();
}

void GUI::Inventory::deleteItem()
{
}

void GUI::Inventory::placeItem()
{
	if (this->checkNewPosition())
	{
		this->_items[_selectedItemIndex].get()->setPositionOnGrid(this->getNewPositionIndex());
	}
	else
	{
		this->_items[_selectedItemIndex].get()->setPosition(this->_originalPosition);
	}

	this->isSelceted = false;
}

bool GUI::Inventory::hasClicked()
{
	return sf::Mouse::isButtonPressed(sf::Mouse::Left);
}

void GUI::Inventory::showItemStats(int itemIndex)
{
}

void GUI::Inventory::selectItem()
{
	for (int index = 0; index < this->_items.size(); index++)
	{
		if (_items[index].get()->getRect().contains((sf::Vector2f)sf::Mouse::getPosition()))
		{
			this->_selectedItemIndex = index;
			this->_originalPosition = _items[index].get()->getPosition();
			this->isSelceted = true;
			return;
		}
	}
}
/*
void GUI::Inventory::updateStatText(Component::Healt health, Component::Mana mana, Component::Speed speed,
	Component::Damage damage, Component::Defence defence, Component::Luck luck)
{
	this->statsString = "Max Healt : " + std::to_string(health.maxHealt)
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
	this->stats.changeString(this->statsString);
}
*/

GUI::Inventory::Inventory(sf::Vector2f windowSize)
{
	AssetManager::loadTexture("Inventory", "NewSprites/Inventory.png");
	AssetManager::loadTexture("InventoryItems", "NewSprites/GUI_ITEM_SPRITES.png");

	this->_inventoryBackground.setTexture(AssetManager::getTexture("Inventory"));

	const sf::Vector2f spriteSize = { this->_inventoryBackground.getGlobalBounds().width,
		this->_inventoryBackground.getGlobalBounds().height };

	this->_inventoryBackground.setOrigin(spriteSize.x/2.f,spriteSize.y/2.f);
	this->_inventoryBackground.setPosition(windowSize.x / 2.f, windowSize.y / 2.f);
	this->_inventoryBackground.scale(std::round((windowSize.y / spriteSize.y) - 2.f),
		std::round((windowSize.y / spriteSize.y) - 2.f));

	this->stats.setText(30, "TempText", sf::Vector2f(windowSize.x/2.25f,
		this->_inventoryBackground.getPosition().y / 2.f));

	//updateStatText(&stats);
	this->addNewItem();
}

void GUI::Inventory::update()
{
	//if (!this->showInventory) { return; }

	if (!this->hasClicked())
	{ 
		if (this->isSelceted)
		{
			this->placeItem();
		}

		return;
	}

	if (this->isSelceted)
	{
		this->_items[this->_selectedItemIndex]
			.get()->setPosition(sf::Vector2f( (float) sf::Mouse::getPosition().x, 
			(float) sf::Mouse::getPosition().y - this->_items[this->_selectedItemIndex]
			.get()->getRect().height / 2.f));
	}
	else
	{
		this->selectItem();
	}
}

void GUI::Inventory::render(sf::RenderTarget* window)
{
	//if (!this->showInventory) { return; }
	window->draw(this->_inventoryBackground);
	window->draw(this->stats.getText());
	
	for (auto& item : _items)
	{
		item.get()->render(window);
	}
}


void GUI::Inventory::addNewItem()
{
	this->_items.push_back(std::make_unique<Item>("InventoryItems",
		sf::IntRect(48, 16, 16, 16), this->_inventoryBackground.getGlobalBounds()));
}

bool GUI::Inventory::checkNewPosition()
{
	sf::Vector2i newPos = this->getNewPositionIndex();
	return ( (newPos.x == 2 || newPos.x == 9) && (newPos.y >= 0 && newPos.y <= 6) );
}

sf::Vector2i GUI::Inventory::getNewPositionIndex()
{	
	sf::Vector2f blockSize(this->_inventoryBackground.getGlobalBounds().width / 10.f, 
		this->_inventoryBackground.getGlobalBounds().height / 9.f);

	sf::Vector2i newPos = { (int)(std::floorf( (float) sf::Mouse::getPosition().x / blockSize.x))-4,
		(int)( std::floorf( (float)sf::Mouse::getPosition().y / blockSize.y))-2 };

	return newPos;
}
