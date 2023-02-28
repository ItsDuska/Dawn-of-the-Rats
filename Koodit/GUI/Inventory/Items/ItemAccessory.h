#pragma once
#include "../Item.h"



class Accessory : Item
{
	float healt;
	float speed;
	float armor;
	float damage;
	float luck;

	void setAttributes(); // laittaa arvot näille
};
