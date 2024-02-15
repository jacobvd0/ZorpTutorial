#include <iostream>
#include <Windows.h>
#include <random>
#include <time.h>

const char* CSI = "\x1b[";
const char* TITLE = "\x1b[5;20H";
const char* INDENT = "\x1b[5C";
const char* YELLOW = "\x1b[93m";
const char* MAGENTA = "\x1b[95m";
const char* RED = "\x1b[91m";
const char* BLUE = "\x1b[94m";
const char* WHITE = "\x1b[97m";
const char* GREEN = "\x1b[92m";
const char* RESET_COLOR = "\x1b[0m";
const int EMPTY = 0;
const int ENEMY = 1;
const int TREASURE = 2;
const int FOOD = 3;
const int ENTERANCE = 4;
const int EXIT = 5;
const int MAX_RANDOM_TYPE = FOOD + 1;

const int MAZE_WIDTH = 10;
const int MAZE_HEIGHT = 6;

const int INDENT_X = 5;
const int ROOM_DESC_Y = 8;
const int MOVEMENT_DESC_Y = 9;
const int MAP_Y = 13;
const int PLAYER_INPUT_X = 30;
const int PLAYER_INPUT_Y = 11;

const int WEST = 4;
const int EAST = 6;
const int NORTH = 8;
const int SOUTH = 2;

bool enableVirtualTerminal() {
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

void initialize(int map[MAZE_HEIGHT][MAZE_WIDTH]) {
    srand(time(nullptr));

    // Fill the arrays with random room types
    for (int y = 0; y < MAZE_HEIGHT; y++) {
        for (int x = 0; x < MAZE_WIDTH; x++) {
            int type = rand() % (MAX_RANDOM_TYPE * 2);
            if (type < MAX_RANDOM_TYPE)
                map[y][x] = type;
            else
                map[y][x] = EMPTY;
            //rooms[y][x] = rand() % MAX_RANDOM_TYPE;
        }
    }

    // Set enterence and exit of the maze
    map[0][0] = ENTERANCE;
    map[MAZE_HEIGHT - 1][MAZE_WIDTH - 1] = EXIT;
}

void drawWelcomeMessage() {
    std::cout << TITLE << MAGENTA << "Welcome to ZORP!" << RESET_COLOR << std::endl;
    std::cout << INDENT << "ZORP is a game of adventure, dangerm and low cunning.\n";
    std::cout << INDENT << "It is definetly not related to any other text-based adventure game.\n";
}

void drawRoom(int map[MAZE_HEIGHT][MAZE_WIDTH], int x, int y) {
    int outX = INDENT_X + (6 * x) + 1;
    int outY = MAP_Y + y;

    std::cout << CSI << outY << ";" << outX << "H";
    switch (map[y][x]) {
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

void drawMap(int map[MAZE_HEIGHT][MAZE_WIDTH]) {
    // reset draw colors
    std::cout << RESET_COLOR;
    for (int y = 0; y < MAZE_HEIGHT; y++) {
        std::cout << INDENT;
        for (int x = 0; x < MAZE_WIDTH; x++) {
            drawRoom(map, x, y);
        }
        std::cout << std::endl;
    }
}

void drawRoomDescription(int roomType) {
    // reset draw colors
    std::cout << RESET_COLOR;
    // jump to the correct location
    std::cout << CSI << ROOM_DESC_Y << ";" << 0 << "H";
    // Delete 4 lines and insert 4 empty lines
    std::cout << CSI << "4M" << CSI << "4L" << std::endl;

    // Write description of current room
    switch (roomType) {
    case EMPTY:
        std::cout << INDENT << "You are in an empty meadow. There is nothing of note here.\n";
        break;
    case ENEMY:
        std::cout << INDENT << "BEWARE. An enemy is approaching.\n";
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

void drawPlayer(int x, int y) {
    int outX = INDENT_X + (6 * x) + 3;
    int outY = MAP_Y + y;

    // draw player's pos on the map
    // move cursor the map pos and delete character at that position
    std::cout << CSI << outY << ";" << outX << "H";
    std::cout << MAGENTA << "\x81" << RESET_COLOR;
}

void drawValidDirections(int x, int y) {
    // reset draw colors
    std::cout << RESET_COLOR;

    // jump to the correct location
    std::cout << CSI << MOVEMENT_DESC_Y + 1 << ";" << 0 << "H";
    std::cout << INDENT << "You can see paths leading to the " << ((x > 0) ? "west, " : "") << ((x < MAZE_WIDTH - 1) ? "east, " : "") << ((y > 0) ? "north, " : "") << ((y < MAZE_HEIGHT - 1) ? "south, " : "") << std::endl;
}

int getMovementDirection() {
    // jump to the correct location
    std::cout << CSI << PLAYER_INPUT_Y << ";" << 0 << "H";
    std::cout << INDENT << "Where to now?";

    int direction;
    // move cursor to position for player to enter input
    std::cout << CSI << PLAYER_INPUT_Y << ";" << PLAYER_INPUT_X << "H" << YELLOW;

    // clear input buffer
    std::cin.clear();
    std::cin.ignore(std::cin.rdbuf()->in_avail());

    std::cin >> direction;
    std::cout << RESET_COLOR;

    if (std::cin.fail())
        return 0;
    return direction;
}

int main()
{
    // Create a 2D array
    int rooms[MAZE_HEIGHT][MAZE_WIDTH];

    bool gameOver = false;
    int playerX = 0;
    int playerY = 0;

    // try enable the virtual terminal, exit if it doesn't work
    if (!enableVirtualTerminal()) {
        std::cout << "The virtual terminal processing mode could not be activated.\n";
        std::cout << "Press 'Enter' to exit.\n";
        std::cin.get();
        return 0;
    }

    // initialize the rooms
    initialize(rooms);

    // draw the welcome message
    drawWelcomeMessage();
    
    // output the map
    drawMap(rooms);

    // game loop
    while (!gameOver) {
        drawRoomDescription(rooms[playerY][playerX]);

        drawPlayer(playerX, playerY);

        if (rooms[playerY][playerX] == EXIT) {
            gameOver = true;
            continue;
        }

        // List directions the player can take then ask for the direction
        drawValidDirections(playerX, playerY);
        int direction = getMovementDirection();

        // Redraw the old room before moving the player
        drawRoom(rooms, playerX, playerY);


        switch (direction) {
        case EAST:
            if (playerX < MAZE_WIDTH - 1)
                playerX++;
            break;
        case WEST:
            if (playerX > 0)
                playerX--;
            break;
        case NORTH:
            if (playerY > 0)
                playerY--;
            break;
        case SOUTH:
            if (playerY < MAZE_HEIGHT - 1)
                playerY++;
            break;
        default:
            break;
        }
        
    }

    std::cout << CSI << PLAYER_INPUT_Y << ";" << 0 << "H";

    std::cout << std::endl << INDENT << "Press 'Enter' to exit the program.\n";
    std::cin.get();
    return 0;
}

