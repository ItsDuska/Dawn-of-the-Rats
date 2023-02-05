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

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		keyPressed = true;
		animationSpeed = 0.2f;
		this->currentAnimationFrames = this->allAnimationFrames[4];
	}

	else if (!keyPressed){
		animationSpeed = 0.1f;
		this->direction = { 0,0 };
		this->currentAnimationFrames = this->allAnimationFrames[0];
	}
	
	

	this->animationHandler.changeAnimation(this->currentAnimationFrames,animationSpeed);
}

void Player::accelerationHandler()
{
	this->velocity.x += this->acceleration * this->direction.x;

	if (this->velocity.x > 0.f && this->velocity.x > this->maxVelocity)
	{
		this->velocity.x = this->maxVelocity;
	}
	else if (this->velocity.x < 0.f && this->velocity.x < -this->maxVelocity)
	{
		this->velocity.x = -this->maxVelocity;
	}

	// y velocity hommelit tähä
}

void Player::decelerationHandler()
{
	if (this->velocity.x > 0.f)
	{
		this->velocity.x -= this->deceleration;
		if (this->velocity.x < 0.f) { this->velocity.x = 0.f; }
	}
	else if (this->velocity.x < 0.f)
	{
		this->velocity.x += this->deceleration;
		if (this->velocity.x > 0.f) { this->velocity.x = 0.f; }
	}
}

Player::Player() : animationHandler(&this->player,0.1f, sf::Vector2i(16, 16), 6, 0)
{ 
	AssetManager::loadTexture("Player", "Kuvat/NewSprites/PlayerSheet.png");
	this->player.setTexture(AssetManager::getTexture("Player"));
	this->player.scale(8.f, 8.f);
	this->player.setPosition(400, 400);	
}

Player::~Player()
{
}

void Player::update()
{
	this->inputs();
	this->animationHandler.update(facingLeft);
	this->accelerationHandler();
	this->decelerationHandler();
	this->player.move(this->velocity);
	
}

void Player::render(sf::RenderTarget* window)
{
	window->draw(this->player);
}

sf::Vector2f Player::getPosition()
{
	return this->player.getPosition();
}
