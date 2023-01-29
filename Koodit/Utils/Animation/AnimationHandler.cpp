#include "AnimationHandler.h"

AnimationHandler::AnimationHandler(sf::Sprite *target, float delay, sf::Vector2i frameResolution,sf::Int8 maxFrames)
{
	this->sprite = target;
	this->totalProgress = 0.0f;
	this->lastFrame = 0;
	this->frameResolution = frameResolution;
	this->TOTAL_FRAMES = maxFrames;
	this->delay = delay;
	sprite->setTextureRect(sf::IntRect(0, 0, this->frameResolution.x, this->frameResolution.y));
}

void AnimationHandler::update(float deltaTime)
{
	this->totalProgress += deltaTime;
	this->totalProgress += this->delay;

	//if (this->totalProgress >= this->delay) { this->totalProgress -= this->delay; }

	if (this->totalProgress >= this->TOTAL_FRAMES)
	{
		this->totalProgress = 0;
	}
	if (this->lastFrame == (int)this->totalProgress)
	{
		return;
	}
	this->totalProgress -= this->delay;
	this->lastFrame = (int)this->totalProgress;
	sprite->setTextureRect(sf::IntRect((int)this->totalProgress * this->frameResolution.x, 0, this->frameResolution.x, this->frameResolution.y));
}