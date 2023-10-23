#pragma once
#include <vector>
#include <SFML/Graphics/Sprite.hpp>
#include <iostream>

class AnimationHandler {
private:
	std::vector<sf::IntRect> frames;
	sf::Vector2i frameResolution;
	sf::Sprite* sprite;
	sf::Int8 lastFrame;
	sf::Int8 TOTAL_FRAMES;
	sf::Int8 STARTING_FRAME;
	float totalProgress;
	float delay;
public:
	AnimationHandler(sf::Sprite *target,float delay,sf::Vector2i frameResolution, sf::Int8 maxFrames, sf::Int8 firstFrame = 0);
	void update(bool facingLeft);
	void changeAnimation(sf::Vector2i newFrames, float speed);
};