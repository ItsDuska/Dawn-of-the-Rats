#include "Player.h"

void Player::inputs()
{
	float animationSpeed;
	bool keyPressed = false;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
	{
		facingLeft = false;
		keyPressed = true;
		animationSpeed = 0.125;
		this->direction.x = this->SPEED;
		this->currentAnimationFrames = this->allAnimationFrames[1];
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
	{
		facingLeft = true;
		keyPressed = true;
		animationSpeed = 0.125;
		this->direction.x = -this->SPEED;
		this->currentAnimationFrames = this->allAnimationFrames[1];
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space))
	{
		keyPressed = true;
		animationSpeed = 0.07f;
		this->currentAnimationFrames = this->allAnimationFrames[2];
	}

	else if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		keyPressed = true;
		animationSpeed = 0.2f;
		this->direction = { 0,0 };
		this->currentAnimationFrames = this->allAnimationFrames[4];
	}

	else if (!keyPressed){
		animationSpeed = 0.1f;
		this->direction = { 0,0 };
		this->currentAnimationFrames = this->allAnimationFrames[0];
	}
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Tab))
	{
		if (this->clock.getElapsedTime().asSeconds() > this->cooldownTime.asSeconds())
		{
			this->_inventory.showInventory = !this->_inventory.showInventory;
			this->clock.restart();
		}
	}
	
	this->animationHandler.changeAnimation(this->currentAnimationFrames,animationSpeed);
}




Player::Player() 
	: animationHandler(&this->sprite,0.1f, sf::Vector2i(16, 16), 6, 0), 
	_inventory(sf::Vector2f((float)sf::VideoMode::getDesktopMode().width, (float)sf::VideoMode::getDesktopMode().height),stats)
{ 
	AssetManager::loadTexture("Player", "NewSprites/PlayerSheet.png");
	this->setTexture("Player");

	
	this->sprite.setOrigin({ this->sprite.getGlobalBounds().width / 2, this->sprite.getGlobalBounds().height / 2 });
	this->sprite.scale(8.f, 8.f);
	this->sprite.setPosition(sf::Vector2f((float)sf::VideoMode::getDesktopMode().width/2, (float)sf::VideoMode::getDesktopMode().height));

	//HIIITBOOOOX
	float newPos = 0.5f * this->sprite.getGlobalBounds().width;

	this->hitboxes.setOrigin({(this->sprite.getGlobalBounds().width / 2)-newPos/2, this->sprite.getGlobalBounds().height / 2 });
	this->hitboxes.setSize({ newPos, this->sprite.getGlobalBounds().height });
	//HIIITBOOOOX

	this->hitboxes.setOutlineColor(sf::Color::Red);
	this->hitboxes.setOutlineThickness(2);
	this->hitboxes.setFillColor(sf::Color::Transparent);
	

}

Player::~Player()
{
}

void Player::update()
{
	this->inputs();
	this->_inventory.update();
	this->animationHandler.update(facingLeft);
	this->accelerationHandler(this->direction);
	this->decelerationHandler();

	

	this->moveEntity(&this->sprite);
	this->hitboxes.setPosition(this->sprite.getPosition());
}

void Player::render(sf::RenderTarget* window)
{
	window->draw(this->sprite);
	window->draw(this->hitboxes);
}

void Player::renderInventory(sf::RenderTarget* window)
{
	this->_inventory.render(window);
}


