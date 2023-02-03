#include "AnimationHandler.h"


AnimationHandler::AnimationHandler(sf::Sprite *target, float delay, sf::Vector2i frameResolution,sf::Int8 maxFrames,sf::Int8 firstFrame)
{
	this->sprite = target;
	this->totalProgress = 0.0f;
	this->lastFrame = 0;
	this->frameResolution = frameResolution;
	this->TOTAL_FRAMES = maxFrames;
	this->delay = delay;
	this->STARTING_FRAME = firstFrame;
	sprite->setTextureRect(sf::IntRect(0, 0, this->frameResolution.x, this->frameResolution.y));
}

void AnimationHandler::update(bool facingLeft)
{
	this->totalProgress += this->delay;
	

	if (this->totalProgress >= this->TOTAL_FRAMES)
	{
		this->totalProgress = this->STARTING_FRAME;
	}
	if (this->lastFrame == (int)this->totalProgress)
	{
		return;
	}
	
	this->lastFrame = (int)this->totalProgress;
	this->sprite->setTextureRect(sf::IntRect((int)this->totalProgress * this->frameResolution.x, 0, this->frameResolution.x, this->frameResolution.y));

	if (facingLeft)
	{
		if (this->sprite->getScale().x > 0)
		{
			this->sprite->setOrigin(10, 0);
			this->sprite->scale(-1.f, 1);
		}
	}
	else {
		if (this->sprite->getScale().x < 0)
		{
			this->sprite->setOrigin(0, 0);
			this->sprite->scale(-1.f, 1);
		}
	}
}

void AnimationHandler::changeAnimation(sf::Vector2i newFrames, float speed)
{
	if (this->STARTING_FRAME == newFrames.x && this->TOTAL_FRAMES == newFrames.y) { return; }
	this->STARTING_FRAME = newFrames.x;
	this->TOTAL_FRAMES = newFrames.y;
	this->delay = speed;
	this->totalProgress = this->STARTING_FRAME;
}
