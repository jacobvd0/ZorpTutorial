#include "Game.h"
#include <iostream>
#include <Windows.h>
#include <random>
#include <time.h>

Game::Game() : m_gameOver{ false }
{
}

Game::~Game()
{
}

bool Game::startup()
{
	if (!enableVirtualTerminal()) {
		std::cout << "The virtual terminal processing mode could not be activated.\n";
		std::cout << "Press 'Enter' to exit.\n";
		std::cin.get();
		return false;
	}

	initializeMap();

	m_player.setPosition(Point2D{ 0,0 });

	drawWelcomeMessage();
	
	return true;
}

void Game::update()
{
	Point2D playerPos = m_player.getPosition();

	if (m_map[playerPos.y][playerPos.x].getType() == EXIT) {
		m_gameOver = true;
		return;
	}

	int command = getCommand();

	if (m_player.executeCommand(command))
		return;

	m_map[playerPos.y][playerPos.x].executeCommand(command);
}

void Game::draw()
{
	Point2D playerPos = m_player.getPosition();

	// list directions the player can take
	drawValidDirections();

	// draw the descripion of the current room
	m_map[playerPos.y][playerPos.x].drawDescription();

	// redraw the map
	drawMap();
	// draw the player
	m_player.draw();
}

bool Game::isGameOver()
{
	return m_gameOver;
}

bool Game::enableVirtualTerminal()
{
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	if (hOut == INVALID_HANDLE_VALUE)
		return false;

	DWORD dwMode = 0;
	if (!GetConsoleMode(hOut, &dwMode))
		return false;

	dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
	if (!SetConsoleMode(hOut, dwMode))
		return false;

	return true;
}

void Game::initializeMap() {
	srand(time(nullptr));

	// Fill the arrays with random room types
	for (int y = 0; y < MAZE_HEIGHT; y++) {
		for (int x = 0; x < MAZE_WIDTH; x++) {
			int type = rand() % (MAX_RANDOM_TYPE * 2);
			if (type < MAX_RANDOM_TYPE)
				m_map[y][x].setType(type);
			else
				m_map[y][x].setType(EMPTY);
			m_map[y][x].setPosition(Point2D{ x,y });
		}
	}

	// Set enterence and exit of the maze
	m_map[0][0].setType(ENTERANCE);
	m_map[MAZE_HEIGHT - 1][MAZE_WIDTH - 1].setType(EXIT);
}

void Game::drawWelcomeMessage()
{
	std::cout << TITLE << MAGENTA << "Welcome to ZORP!" << RESET_COLOR << std::endl;
	std::cout << INDENT << "ZORP is a game of adventure, dangerm and low cunning.\n";
	std::cout << INDENT << "It is definetly not related to any other text-based adventure game.\n";
}

void Game::drawMap()
{
	Point2D position = { 0,0 };

	// reset draw colors
	std::cout << RESET_COLOR;
	for (position.y = 0; position.y < MAZE_HEIGHT; position.y++) {
		std::cout << INDENT;
		for (position.x = 0; position.x < MAZE_WIDTH; position.x++) {
			m_map[position.y][position.x].draw();
		}
		std::cout << std::endl;
	}
}

void Game::drawValidDirections()
{
	Point2D position = m_player.getPosition();

	// reset draw colors
	std::cout << RESET_COLOR;

	// jump to the correct location
	std::cout << CSI << MOVEMENT_DESC_Y + 1 << ";" << 0 << "H";
	std::cout << INDENT << "You can see paths leading to the " << ((position.x > 0) ? "west, " : "") << ((position.x < MAZE_WIDTH - 1) ? "east, " : "") << ((position.y > 0) ? "north, " : "") << ((position.y < MAZE_HEIGHT - 1) ? "south, " : "") << std::endl;
}

int Game::getCommand()
{
	char input[50] = "\0";

	// jump to correct location
	std::cout << CSI << PLAYER_INPUT_Y << ";" << 0 << "H";
	// clear anmy existing text
	std::cout << CSI << "4M";

	std::cout << INDENT << "Enter a command.";
	// move to input field for player to enter text
	std::cout << CSI << PLAYER_INPUT_Y << ";" << PLAYER_INPUT_X << "H" << YELLOW;

	std::cin.clear();
	std::cin.ignore(std::cin.rdbuf()->in_avail());

	std::cin >> input;
	std::cout << RESET_COLOR;

	bool bMove = false;
	while (input) {
		if (strcmp(input, "move") == 0) {
			bMove = true;
		}
		else if (bMove == true) {
			if (strcmp(input, "north") == 0)
				return NORTH;
			if (strcmp(input, "south") == 0)
				return SOUTH;
			if (strcmp(input, "east") == 0)
				return EAST;
			if (strcmp(input, "west") == 0)
				return WEST;
		}

		if (strcmp(input, "look") == 0)
			return LOOK;
		if (strcmp(input, "fight") == 0)
			return FIGHT;

		char next = std::cin.peek();
		if (next == '\n' || next == EOF)
			break;
		std::cin >> input;
	}
	return 0;
}
