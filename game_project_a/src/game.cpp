#include "game_project_a/game.h"

#include "GLFW/glfw3.h"

bool Game::Init(int argc, char **argv)
{
    if(glfwInit()) {
        return false;
    }
    return true;
}

int Game::Run()
{
    return 0;
}
