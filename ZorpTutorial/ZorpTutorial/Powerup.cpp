#include "Powerup.h"
#include <iostream>

Powerup::Powerup(const char name[30], float health, float attack, float defense)
{
	strcpy_s(m_name, 30, name);
	m_healthMultiplier = health;
	m_attackMultiplier = attack;
	m_defenseMultiplier = defense;
}

Powerup::~Powerup()
{
}

char* Powerup::getName()
{
	return m_name;
}

float Powerup::getHealthMultiplier()
{
	return m_healthMultiplier;
}

float Powerup::getAttackMultiplier()
{
	return m_attackMultiplier;
}

float Powerup::getDefenseMultiplier()
{
	return m_defenseMultiplier;
}
