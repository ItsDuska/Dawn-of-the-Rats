#pragma once

class PlayerStats
{
public:
	const float MAXHEALT = 100.f;
	const float MAXMANA = 100.f;
	float currentHealt = 100.f;
	float currentMana = 100.f;
	float healtRegen = 0.1f;
	float manaRegen = 0.25f;
	float speed = 0.5f;
	float luck = 1.f;
	float defense = 10.f;
	float damage = 5.f;
};