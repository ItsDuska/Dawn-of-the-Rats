#pragma once
#include "System/ECS/Systems/System.h"
#include "System/ECS/Coordinator/Cordinator.h"
#include <cmath>
#include <algorithm>


class FollowSystem : public System
{
public:
	void update(Coordinator& entityManager, float dt);
private:
	float evaluate(float x);
	float clamp(float x, float upper, float lower);
	float lerp(float a, float b, float f);
	float floating(float x);
	float PI = 3.14159f;
	bool isClose(sf::Vector2f pos, sf::Vector2f pos2, float offset);
};

