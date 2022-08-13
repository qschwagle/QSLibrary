//
// Created by Quinton Schwagle on 8/13/22.
//

#include "game_tfe/game_2048.h"
#include <iostream>

Game2048::Game2048()
{

}

Game2048::~Game2048() noexcept
{
    if(mWindow) {
        glfwDestroyWindow(mWindow);
    }

    glfwTerminate();
}

bool Game2048::Init(int argc, char **argv)
{
    if(glfwInit()) {
        std::cerr << "Could not initialize glfw. Aborting" << std::endl;
        return false;
    }

    mWindow = glfwCreateWindow(1280, 720, "2048", NULL, NULL);

    if(!mWindow) {
        std::cerr << "Could not create glfw window. Aborting" << std::endl;
        return false;
    }

    glfwMakeContextCurrent(mWindow);
    glfwSwapInterval(1);
}

int Game2048::Run()
{
}

int Game2048::Draw()
{
}

