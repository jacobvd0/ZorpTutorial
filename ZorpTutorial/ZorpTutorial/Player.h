#pragma once
#include "Point2D.h"
#include "Powerup.h"
#include <vector>
class Room;

class Player
{
public:
	Player();
	Player(int x, int y);
	~Player();

	void setPosition(Point2D position);

	Point2D getPosition();

	void draw();

	bool executeCommand(int command, Room* pRoom);

private:
	bool pickup(Room* room);

	Point2D m_mapPosition;
	std::vector<Powerup> m_powerups;
	
	int m_healthPoints;
	int m_attackPoints;
	int m_defendPoints;
};

