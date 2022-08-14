//
// Created by Quinton Schwagle on 8/13/22.
//

#include "game_tfe/game_2048.h"

#include <iostream>
#include <functional>

#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "linalg/rvector.h"

/**
 * callback registered on glfw window to respond to window size change events
 * \param window glfw window
 * \param width next width of window
 * \param height next height of window
 */
void FrameBufferSizeCallback(GLFWwindow* window, int width, int height)
{
    // just update the view port for right now
    glViewport(0, 0, width, height);
    Game2048* game = static_cast<Game2048*>(glfwGetWindowUserPointer(window));
    WindowProperties& props = game->GetWindowProperties();
    props.width = width;
    props.height = height;
}

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
    if(!glfwInit()) {
        std::cerr << "Could not initialize glfw. Aborting" << std::endl;
        return false;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    mWindow = glfwCreateWindow(1280, 720, "2048", NULL, NULL);

    if(!mWindow) {
        std::cerr << "Could not create glfw window. Aborting" << std::endl;
        return false;
    }

    glfwMakeContextCurrent(mWindow);


    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "failed to initialize glad. Aborting" << std::endl;
        return false;
    }

    glfwSetFramebufferSizeCallback(mWindow, &FrameBufferSizeCallback);
    glfwSetWindowUserPointer(mWindow, this);
    

    glViewport(0,0, 1280, 720);

    glfwSwapInterval(1);
    
    return true;
}

int Game2048::Run()
{
    RVector<4> color = { 1.0f, 0.0f, 0.0f, 1.0f };

    while(!glfwWindowShouldClose(mWindow)) {
        ProcessKeyboardInput();

        glClearColor(color[0], color[1], color[2], color[3]);
        glClear(GL_COLOR_BUFFER_BIT);

        Draw();

        glfwSwapBuffers(mWindow);
        glfwPollEvents();
    }
    return 0;
}

int Game2048::Draw()
{
    return 0;
}

void Game2048::ProcessKeyboardInput()
{
    if(glfwGetKey(mWindow, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(mWindow, true);
    }
}

