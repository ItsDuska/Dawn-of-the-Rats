#pragma once
#include <SFML/Graphics.hpp>


class AnimationHandler
{
private:
	int currentFrame;
	float FrameTime;
	const float maxFrameTime;

	sf::Texture textures[];
	~AnimationHandler();
	void addTexture();
public:
	AnimationHandler(std::string filenames[], std::string path);
	void update();

};

