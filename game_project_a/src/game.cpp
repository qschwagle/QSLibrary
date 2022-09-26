#include "game_project_a/game.h"

#include <sstream>

#include "glad/glad.h"
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

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);

    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    if(!((mWindow = glfwCreateWindow(1280, 720, "Hello World", nullptr, nullptr)))) {
        auto msg = std::stringstream("Game::Init: Unable to create window. should terminate");
        mLogger->WriteCritical(msg);
        return false;
    }

    glfwMakeContextCurrent(mWindow);

    glfwSwapInterval(1);

    if(!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        auto msg = std::stringstream("Game::Init: failed to initialize glad. should terminate");
        mLogger->WriteCritical(msg);
        return false;
    }

    glViewport(0, 0, 1280, 720);

    return true;
}

int Game::Run()
{
    while(!glfwWindowShouldClose(mWindow)) {

        glClearColor(1.0, 0.0, 0.0, 1.0);
        glClear(GL_COLOR_BUFFER_BIT);

        glfwSwapBuffers(mWindow);

        glfwWaitEventsTimeout(0.001);
    }
    return 0;
}
