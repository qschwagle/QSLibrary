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
#include "linalg/cmatrix.h"
#include "geometry/geometry.h"

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


    glfwSwapInterval(1);


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
        layout (location = 1) in vec4 aColor;

        out vec4 Color;

        uniform mat4 proj;

        void main()
        {
            gl_Position = proj * vec4(aPos.x, aPos.y, aPos.z, 1.0);
            Color = aColor;
        }
    )""";

    std::string fragment_shader_src = R"""(
        #version 330 core
        in  vec4 Color;
        out vec4 FragColor;
        void main()
        {
            FragColor = Color;
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

    CreateRectangle3D<7>(mGeometry, RVector<3>{10.0f, 10.0f, 0.0f}, RVector<4>{0.0f, 1.0f, 0.0f, 1.0f}, 100.0f, 100.0f); 

    std::cout << "mGeometry vertices: " << mGeometry.GetVerticesCount() << std::endl;
    std::cout << "mGeometry indices: " << mGeometry.GetIndicesCount() << std::endl;

    mBuffer.Init();

    mBuffer.LoadData(reinterpret_cast<unsigned char*>(mGeometry.GetVerticesPointer()), sizeof(float) * mGeometry.GetVerticesCount()*7, mGeometry.GetIndicesPointer(), mGeometry.GetIndicesCount() * sizeof(unsigned int), GLBuffer::GLUsage::STATIC);

    mBuffer.SetAttributePointer(0, 3, GLBuffer::GLDataType::FLOAT, 7 * sizeof(float), 0);
    mBuffer.SetAttributePointer(1, 4, GLBuffer::GLDataType::FLOAT, 7 * sizeof(float), reinterpret_cast<void*>(sizeof(float)*3));

    CMatrix<4,4> proj = OrthographicProjection(0, mWindowProperties.width, mWindowProperties.height, 0, 1.0f, 0.0f);

    std::string projection_name = "proj";
    auto uniform = mGLProgram.GetUniform(projection_name).value();
    uniform.SetMat4fv(proj.GetData());

    return true;
}

int Game2048::Run()
{
    RVector<4> color = { 1.0f, 0.0f, 0.0f, 1.0f };


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
    glDrawElements(GL_TRIANGLES, mGeometry.GetIndicesCount(), GL_UNSIGNED_INT, 0);
    return 0;
}

void Game2048::ProcessKeyboardInput()
{
    if(glfwGetKey(mWindow, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(mWindow, true);
    }
}

