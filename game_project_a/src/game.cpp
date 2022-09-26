#include "game_project_a/game.h"

#include <sstream>

#include "GLFW/glfw3.h"

Game::Game() noexcept
{
}

Game::~Game()
{
    if(mWindow) glfwDestroyWindow(mWindow);
    if(mGLFWInitialized) glfwTerminate();
}


bool Game::Init(int argc, char **argv)
{
    if(!glfwInit()) {
        auto msg = std::stringstream("Game::Init: Unable to initialize glfw. should terminate");
        mLogger->WriteCritical(msg);
        return false;
    }
    mGLFWInitialized = true;

    if(!((mWindow = glfwCreateWindow(1280, 720, "Hello World", nullptr, nullptr)))) {
        auto msg = std::stringstream("Game::Init: Unable to create window. should terminate");
        mLogger->WriteCritical(msg);
        return false;
    }

    return true;
}

int Game::Run()
{
    while(!glfwWindowShouldClose(mWindow)) {

        glfwWaitEventsTimeout(0.100);
    }
    return 0;
}
