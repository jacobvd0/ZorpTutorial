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
const char* SAVE_CURSOR_POS = "\x1b[s";
const char* RESTORE_CURSOR_POS = "\x1b[u";


int main()
{
    int height = 0;
    char firstLetterOfName = 0;
    int avatarHP = 0;

    const int EMPTY = 0;
    const int ENEMY = 1;
    const int TREASURE = 2;
    const int FOOD = 3;
    const int ENTERANCE = 4;
    const int EXIT = 5;
    const int MAX_RANDOM_TYPE = FOOD + 1;

    const int MAZE_WIDTH = 10;
    const int MAZE_HEIGHT = 6;

    // Create a 2D array
    int rooms[MAZE_HEIGHT][MAZE_WIDTH];

    srand(time(nullptr));

    // Fill the arrays with random room types
    for (int y = 0; y < MAZE_HEIGHT; y++) {
        for (int x = 0; x < MAZE_WIDTH; x++) {
            int type = rand() % (MAX_RANDOM_TYPE * 2);
            if (type < MAX_RANDOM_TYPE)
                rooms[y][x] = type;
            else
                rooms[y][x] = EMPTY;
            //rooms[y][x] = rand() % MAX_RANDOM_TYPE;
        }
    }
    // Set enterence and exit of the maze
    rooms[0][0] = ENTERANCE;
    rooms[MAZE_HEIGHT - 1][MAZE_WIDTH - 1] = EXIT;

    


    // Set output mode to handle virtual terminal sequences
    DWORD dwMode = 0;
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    GetConsoleMode(hOut, &dwMode);
    dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    SetConsoleMode(hOut, dwMode);

    std::cout << TITLE << MAGENTA << "Welcome to ZORP!" << RESET_COLOR << std::endl;
    std::cout << INDENT << "ZORP is a game of adventure, dangerm and low cunning.\n";
    std::cout << INDENT << "It is definetly not related to any other text-based adventure game.\n";

    std::cout << INDENT << "First, some questions...\n";
    std::cout << SAVE_CURSOR_POS;

    // output the map
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << std::endl;
    for (int y = 0; y < MAZE_HEIGHT; y++) {
        std::cout << INDENT;
        for (int x = 0; x < MAZE_WIDTH; x++) {
            switch (rooms[y][x]) {
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
        std::cout << std::endl;
    }
    // move cursor back to the top of the map
    std::cout << RESTORE_CURSOR_POS;

    std::cout << INDENT << "How tall are you, in centermeters? " << INDENT << YELLOW;

    std::cin >> height;
    std::cout << RESET_COLOR << std::endl;

    if (std::cin.fail()) {
        std::cout << INDENT << "You have failed the first challenge and are eaten by a grue.\n";
    }
    else {
        std::cout << INDENT << "You entered " << height << std::endl;
    }

    std::cin.clear();
    std::cin.ignore(std::cin.rdbuf()->in_avail());
    std::cin.get();

    // move coursor back to the start of the 1st question
    std::cout << RESTORE_CURSOR_POS;

    // Delete the next 4 lines
    std::cout << CSI << "3M";
    // insert 3 lines so the map stays in the same place
    std::cout << CSI << "3L";


    std::cout << INDENT << "What is the first letter of your name?\n";
    std::cin >> firstLetterOfName;

    if (std::cin.fail() || !isalpha(firstLetterOfName)) {
        std::cout << INDENT << "You have failed the second challenge and are eaten by a grue.\n";
    }
    else {
        std::cout << INDENT << "You entered " << firstLetterOfName << std::endl;
    }

    std::cin.clear();
    std::cin.ignore(std::cin.rdbuf()->in_avail());
    std::cin.get();

    // restore cursor position then delete and insert 4 lines
    std::cout << RESTORE_CURSOR_POS << CSI << "A" << CSI << "4M" << CSI << "4L";

    // move coursor back to the start of the 1st question
    //std::cout << RESTORE_CURSOR_POS;

    std::cout << CSI << "A";

    // Delete the next 4 lines
    //std::cout << CSI << "4M";

    if (firstLetterOfName != 0) {
        avatarHP = (float)height / (firstLetterOfName * 0.02f);
    }
    else {
        avatarHP = 0;
    }

    std::cout << INDENT << "Using a complex deterministic algorithm, it has been calculated that you have " << avatarHP << " hit point(s).\n";

    

    std::cout << std::endl << INDENT << "Press 'Enter' to exit the program.\n";
    std::cin.get();
    return 0;
}

