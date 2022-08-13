//
// Created by Quinton Schwagle on 8/13/22.
//

#include <iostream>
#include <game_tfe/game_2048.h>

int main(int argc, char** argv)
{
    Game2048 game;
    if(game.Init(argc, argv)) {
        return EXIT_FAILURE;
    }
    return game.Run();
}

