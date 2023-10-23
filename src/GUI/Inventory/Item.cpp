#include "Item.h"

void Item::setTexture(const std::string spriteName, const sf::IntRect itemArea,sf::FloatRect spriteSize, AssetManager& assetManager)
{

    //testiä varten on const arvot
    const int xPos = 1;
    const int yPos = 0;
   
    /*
    if vasen reuna:
        xPos = 2;
    else:
        xPos = 9
    */
    this->_itemSprite.setTexture(assetManager.getTexture(spriteName));
    this->_itemSprite.setTextureRect(itemArea);
    
    sf::Vector2f blockSize(spriteSize.width / 10.f, spriteSize.height / 9.f);
    this->_itemSprite.setOrigin(this->_itemSprite.getGlobalBounds().width/2.f, this->_itemSprite.getGlobalBounds().height/2.f);

    this->_itemSprite.setPosition(std::floorf((spriteSize.left + xPos* blockSize.x)+blockSize.x/2.f),
        std::floorf((spriteSize.top + (yPos+2) * blockSize.y) + blockSize.x / 2.f));

    this->_itemSprite.scale(std::floorf(blockSize.x* (14.f/16.f) / this->_itemSprite.getGlobalBounds().width),
        std::floorf(blockSize.x * (14.f / 16.f) / this->_itemSprite.getGlobalBounds().height));
    
    this->SpritePositions = { spriteSize.left,spriteSize.top,blockSize.x,blockSize.y };
}

Item::Item(const std::string spriteName, const sf::IntRect itemArea, sf::FloatRect spriteSize, AssetManager& assetManager) // itemName, itemRarity, itemType tarvitaan tähän
{
    //FOR TESTING:
    this->_type = Type::NECKLACE;
    this->_rarity = Rarity::STRANGE;
    this->_itemName = "Aku's Terror";
    this->setTexture(spriteName, itemArea, spriteSize, assetManager);
}

std::string Item::getName()
{
    return this->_itemName;
}

Rarity Item::getRarity()
{
    return this->_rarity;
}

sf::Sprite Item::getSprite()
{
    return this->_itemSprite;
}

sf::FloatRect Item::getRect()
{
    return this->_itemSprite.getGlobalBounds();
}

void Item::setPositionOnGrid(sf::Vector2i indexPos)
{
    this->_itemSprite.setPosition(
        std::floorf((this->SpritePositions.left + indexPos.x * this->SpritePositions.width) - this->SpritePositions.width / 2.f),
        std::floorf((this->SpritePositions.top + (indexPos.y + 2) * this->SpritePositions.height) - this->SpritePositions.height / 2.f));
}

void Item::setPosition(sf::Vector2f newPos)
{
    this->_itemSprite.setPosition(newPos);
}

sf::Vector2f Item::getPosition()
{
    return this->_itemSprite.getPosition();
}

void Item::render(sf::RenderTarget* window)
{
    window->draw(this->_itemSprite);
}
