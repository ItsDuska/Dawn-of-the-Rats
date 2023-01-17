#include "AnimationHandler.h"

void AnimationHandler::addTexture(std::string path,std::vector<std::string>fileNames)
{
	for (int i = 0; i < fileNames.size(); i++) 
	{
		std::string filePath = path;
		filePath.append(fileNames[i]);
		if (!this->textures[i].loadFromFile(filePath))
		{
			std::cout << "ERROR! Can't load file: " << filePath << "\n ";
			return;
		}
	}
}

AnimationHandler::AnimationHandler(std::vector<std::string> fileNames, std::string path,float delay,sf::Sprite *sprite,sf::Vector2f scalingSize)
{
	this->scalingSize = scalingSize;
	this->maxFrames = (float)fileNames.size();
	this->objectsSprite = sprite;
	this->delay = delay;
	this->textures.resize(fileNames.size());
	addTexture(path,fileNames);

}

void AnimationHandler::update()
{
	this->currentFrame += this->delay;
	if (this->currentFrame >= this->maxFrames)
	{
		this->currentFrame = 0;
	}
	if (this->lastFrame == (int)this->currentFrame)
	{
		return;
	}
	this->lastFrame = (int)this->currentFrame;
	this->objectsSprite->setTexture(this->textures[(int)this->currentFrame]);
	if (this->scalingSize != sf::Vector2f(0, 0))
		this->objectsSprite->setScale(this->scalingSize);	
}
