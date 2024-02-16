#include "Room.h"
#include "GameDefines.h"
#include <iostream>

Room::Room() : m_type(EMPTY)
{
}

Room::~Room()
{
}

void Room::setPosition(Point2D position)
{
	m_mapPosition = position;
}

void Room::setType(int type)
{
	m_type = type;
}

int Room::getType()
{
	return m_type;
}

void Room::draw()
{
	// find the output position
	int outX = INDENT_X + (6 * m_mapPosition.x) + 1;
	int outY = MAP_Y + m_mapPosition.y;

	// jump to the correct location
	std::cout << CSI << outY << ";" << outX << "H";

	// draw the room
    switch (m_type) {
    case EMPTY:
        std::cout << "[ " << GREEN << "\xb0" << RESET_COLOR << " ] ";
        break;
    case ENEMY:
        std::cout << "[ " << RED << "\x94" << RESET_COLOR << " ] ";
        break;
    case TREASURE:
        std::cout << "[ " << YELLOW << "$" << RESET_COLOR << " ] ";
        break;
    case FOOD:
        std::cout << "[ " << WHITE << "\xcf" << RESET_COLOR << " ] ";
        break;
    case ENTERANCE:
        std::cout << "[ " << WHITE << "\x9d" << RESET_COLOR << " ] ";
        break;
    case EXIT:
        std::cout << "[ " << WHITE << "\xFE" << RESET_COLOR << " ] ";
        break;
    }
}

void Room::drawDescription()
{
    std::cout << RESET_COLOR;
    std::cout << CSI << ROOM_DESC_Y << ";" << 0 << "H";
    std::cout << CSI << "4M" << CSI << "4L" << std::endl;

    // write the description of the current room
    switch (m_type) {
    case EMPTY:
        std::cout << INDENT << "You are in an empty meadow. There is nothing of note here.\n";
        break;
    case ENEMY:
        std::cout << INDENT << RED << "BEWARE." << RESET_COLOR << " An enemy is approaching.\n";
        break;
    case TREASURE:
        std::cout << INDENT << "Your journey has been rewarded. You have found some treasure.\n";
        break;
    case FOOD:
        std::cout << INDENT << "At last! You collect some food to sustain you on your journey.\n";
        break;
    case ENTERANCE:
        std::cout << INDENT << "The enterance you used to enter this maze is blocked. There is no going back.\n";
        break;
    case EXIT:
        std::cout << INDENT << "Despite all odds, you made it to the exit. Congratulations.\n";
        break;
    }
}

bool Room::executeCommand(int command)
{
    switch (command) {
    case LOOK:
        std::cout << EXTRA_OUTPUT_POS << RESET_COLOR << "You look around, but see nothing worth mentioning\n";
        std::cout << INDENT << "Press 'Enter' to continue";
        std::cin.clear();
        std::cin.ignore(std::cin.rdbuf()->in_avail());
        std::cin.get();
        return true;
    case FIGHT:
        std::cout << EXTRA_OUTPUT_POS << RESET_COLOR << "You could try to fight, but you don't have a weapon\n";
        std::cout << INDENT << "Press 'Enter' to continue";
        std::cin.clear();
        std::cin.ignore(std::cin.rdbuf()->in_avail());
        std::cin.get();
        return true;
    default:
        std::cout << EXTRA_OUTPUT_POS << RESET_COLOR << "You try, but you just can't do it.\n";
        std::cout << INDENT << "Press 'Enter' to continue";
        std::cin.clear();
        std::cin.ignore(std::cin.rdbuf()->in_avail());
        std::cin.get();
    }
    return false;
}
