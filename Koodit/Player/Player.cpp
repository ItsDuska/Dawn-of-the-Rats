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
		this->player.move(6, 0);
		this->currentAnimationFrames = this->allAnimationFrames[1];
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
	{
		facingLeft = true;
		keyPressed = true;
		animationSpeed = 0.125;
		this->player.move(-6, 0);
		this->currentAnimationFrames = this->allAnimationFrames[1];
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space))
	{
		keyPressed = true;
		animationSpeed = 0.07;
		this->currentAnimationFrames = this->allAnimationFrames[2];
	}

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		keyPressed = true;
		animationSpeed = 0.2;
		this->currentAnimationFrames = this->allAnimationFrames[4];
	}

	else if (!keyPressed){
		animationSpeed = 0.1;
		this->currentAnimationFrames = this->allAnimationFrames[0];
	}
	
	

	this->animationHandler.changeAnimation(this->currentAnimationFrames,animationSpeed);
}

Player::Player() : animationHandler(&this->player,0.1f, sf::Vector2i(16, 16), 6, 0)
{
	AssetManager::loadTexture("Player", "Kuvat/NewSprites/PlayerSheet.png");
	this->player.setTexture(AssetManager::getTexture("Player"));
	this->player.scale(8.f, 8.f);
	this->player.setPosition(400, 400);	
}

void Player::update()
{
	this->inputs();
	this->animationHandler.update(facingLeft);
}

void Player::render(sf::RenderTarget* window)
{
	window->draw(this->player);
}

sf::Vector2f Player::getPosition()
{
	return this->player.getPosition();
}
