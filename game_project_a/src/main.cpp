#include <iostream>

#include "game_project_a/game.h"

int main(int argc, char** argv)
{
    Game game;
    if(game.Init(argc, argv)) {
        return game.Run();
    }
}
