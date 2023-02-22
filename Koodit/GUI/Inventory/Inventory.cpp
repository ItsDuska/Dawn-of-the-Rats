#include "Inventory.h"



std::string roundTwo(const float x) {
	std::stringstream ss;
	ss << std::fixed;
	ss.precision(2); // set # places after decimal
	ss << x;
	return ss.str();
}




void Inventory::updateStatText(PlayerStats* stats)
{
	this->statsString = "Max Healt : " +  roundTwo(stats->MAXHEALT) + "\nMax Mana : " + roundTwo(stats->MAXMANA)
		+ "\nCurrent Healt : " + roundTwo(stats->currentHealt)
		+ "\nCurrent Mana : " + roundTwo(stats->currentMana)
		+ "\nAttack : " + roundTwo(stats->damage)
		+ "\nDefense : " + roundTwo(stats->defense)
		+ "\nSpeed : " + roundTwo(stats->speed)
		+ "\nLuck : " + roundTwo(stats->luck);
	this->stats.changeString(this->statsString);


}

Inventory::Inventory(sf::Vector2f windowSize, PlayerStats& stats)
{
	AssetManager::loadTexture("Inventory", "Kuvat/NewSprites/Inventory.png");
	this->_inventoryBackground.setTexture(AssetManager::getTexture("Inventory"));
	const sf::Vector2f spriteSize = { this->_inventoryBackground.getGlobalBounds().width, this->_inventoryBackground.getGlobalBounds().height };
	this->_inventoryBackground.setOrigin(spriteSize.x/2.f,spriteSize.y/2.f);
	this->_inventoryBackground.setPosition(windowSize.x / 2.f, windowSize.y / 2.f);
	this->_inventoryBackground.scale(std::round((windowSize.y / spriteSize.y) - 2.f), std::round((windowSize.y / spriteSize.y) - 2.f));
	this->stats.setText(30, "Jooooop", sf::Vector2f(windowSize.x/2.25f, this->_inventoryBackground.getPosition().y / 2.f));
	updateStatText(&stats);
}

void Inventory::update()
{
	if (!this->showInventory) { return; }
}

void Inventory::render(sf::RenderTarget* window)
{
	if (!this->showInventory) { return; }
	window->draw(this->_inventoryBackground);
	window->draw(this->stats.getText());
}
