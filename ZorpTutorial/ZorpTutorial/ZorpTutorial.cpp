#include <iostream>
#include "Game.h"


int main()
{
    Game game;
    if (game.startup() == false)
        return 0;

    // game loop
    while (!game.isGameOver()) {
        game.draw();
        
        game.update();
    }

    std::cout << CSI << PLAYER_INPUT_Y << ";" << 0 << "H";

    std::cout << std::endl << INDENT << "Press 'Enter' to exit the program.\n";
    std::cin.get();
    return 0;
}

