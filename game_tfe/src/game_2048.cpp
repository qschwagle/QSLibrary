//
// Created by Quinton Schwagle on 8/13/22.
//

#include "game_tfe/game_2048.h"

#include <iostream>
#include <functional>
#include <string>
#include <memory>
#include <vector>

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

    //glfwSwapInterval(1);

    std::string vertex_shader_src = R"""(
        #version 330 core
        layout (location = 0) in vec3 aPos;

        void main()
        {
            gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
        }
    )""";

    std::string fragment_shader_src = R"""(
        #version 330 core
        out vec4 FragColor;
        void main()
        {
            FragColor = vec4(0.0f, 1.0f, 0.0f, 1.0f);
        }
    )""";

    auto vertex_shader = std::make_shared<GLShader>();
    if(!vertex_shader->InitShader(vertex_shader_src, GLShader::GLShaderType::VERTEX)) {
        std::cerr << "Game2048::Init: could not initialize vertex shader" << std::endl;
        return false;
    }

    auto frag_shader = std::make_shared<GLShader>();
    if(!frag_shader->InitShader(fragment_shader_src, GLShader::GLShaderType::FRAGMENT)) {
        std::cerr << "Game2048::Init: could not initialize fragment shader" << std::endl;
        return false;
    }

    mGLProgram.AddVertexShader(vertex_shader);
    mGLProgram.AddFragmentShader(frag_shader);

    if(!mGLProgram.CompileProgram()) {
        std::cerr << "Game2048::Init: could not compile program" << std::endl;
        return false;
    }

    if(!mGLProgram.UseProgram()) {
        std::cerr << "Game2048::Init: could not use program" << std::endl;
        return false;
    }

    mBuffer.Init();

    mBuffer.LoadData(reinterpret_cast<unsigned char*>(mTriangle.data()), sizeof(float) * mTriangle.size(), GLBuffer::GLUsage::STATIC);

    mBuffer.SetAttributePointer(0, 3, GLBuffer::GLDataType::FLOAT, 3 * sizeof(float), 0);

    return true;
}

int Game2048::Run()
{
    RVector<4> color = { 1.0f, 0.0f, 0.0f, 1.0f };

    //glfwSwapInterval(1);

    while(!glfwWindowShouldClose(mWindow)) {
        ProcessKeyboardInput();

        glClearColor(color[0], color[1], color[2], color[3]);
        glClear(GL_COLOR_BUFFER_BIT);


        (void) mGLProgram.UseProgram();
        (void) mBuffer.BindVertexArrayObject();

        Draw();

        glfwSwapBuffers(mWindow);
        //glfwWaitEventsTimeout(0.0001);
        glfwWaitEvents();
    }
    return 0;
}

int Game2048::Draw()
{
    glDrawArrays(GL_TRIANGLES, 0, 3);
    return 0;
}

void Game2048::ProcessKeyboardInput()
{
    if(glfwGetKey(mWindow, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(mWindow, true);
    }
}

