#include "Powerup.h"

Powerup::Powerup(const char name[30], float health, float attack, float defense)
{
}

Powerup::~Powerup()
{
}

char* Powerup::getName()
{
	return nullptr;
}

float Powerup::getHealthMultiplier()
{
	return 0.0f;
}

float Powerup::getAttackMultiplier()
{
	return 0.0f;
}

float Powerup::getDefenseMultiplier()
{
	return 0.0f;
}
