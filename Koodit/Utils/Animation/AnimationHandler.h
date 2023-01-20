#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

class AnimationHandler {
private:
	std::vector<sf::IntRect> frames;
	sf::Vector2i frameResolution;
	sf::Sprite* sprite;
	sf::Int8 lastFrame;
	sf::Int8 TOTAL_FRAMES;
	float totalProgress;
	float delay;
public:
	AnimationHandler(sf::Sprite *target,float delay,sf::Vector2i frameResolution, sf::Int8 maxFrames);
	void update();
};