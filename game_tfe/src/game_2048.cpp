//
// Created by Quinton Schwagle on 8/13/22.
//

#include "game_tfe/game_2048.h"

#include <iostream>
#include <functional>
#include <string>
#include <memory>
#include <vector>
#include <fstream>

#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "linalg/rvector.h"
#include "linalg/cmatrix.h"
#include "geometry/geometry.h"
#include "game_tfe/text.h"

/**
 * converts from 0-255 int to float 0.0f to 1.0f
 * \param r red
 * \param g green
 * \param b blue
 * \returns float vector
 */
static constexpr RVector<4> ColorIntToFloat(unsigned char r, unsigned char g, unsigned char b, unsigned char a)
{
    return RVector<4> { r / 255.0f, g / 255.0f, b / 255.0f, a / 255.0f };
}

/**
 * returns the left position from center point
 * \param container_width containers width
 * \param container_height containers height
 * \param item_width item width
 * \param item_height item height
 * \returns the left coordinate from center
 */
static constexpr RVector<3> CenterOriginLeft(float container_width, float container_height, float item_width, float item_height)
{
    RVector<3> out;
    out[0] = (container_width / 2.0f) - (item_width / 2.0f);
    out[1] = (container_height / 2.0f) - (item_height / 2.0f);
    out[2] = 0.0f;
    return out;
}

/**
 * callback registered on glfw window to respond to window size change events
 * \param window glfw window
 * \param width next width of window
 * \param height next height of window
 */
static void FrameBufferSizeCallback(GLFWwindow* window, int width, int height)
{
    // just update the view port for right now
    glViewport(0, 0, width, height);
    Game2048* game = static_cast<Game2048*>(glfwGetWindowUserPointer(window));
    auto& props = game->GetWindowProperties();
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

    mWindow = glfwCreateWindow(mWindowProperties.width, mWindowProperties.height, "2048", NULL, NULL);

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

    glViewport(0,0, mWindowProperties.width, mWindowProperties.height);

    std::string vertex_shader_src = R"""(
        #version 330 core
        layout (location = 0) in vec3 aPos;
        layout (location = 1) in vec4 aColor;
        layout (location = 2) in vec2 aTexCoord;

        out vec4 Color;
        out vec2 TexCoord;

        uniform mat4 proj;

        void main()
        {
            gl_Position = proj * vec4(aPos.x, aPos.y, aPos.z, 1.0);
            Color = aColor;
            TexCoord = aTexCoord;
        }
    )""";

    std::string fragment_shader_src = R"""(
        #version 330 core
        in vec4 Color;
        in vec2 TexCoord;

        uniform sampler2D Texture;

        out vec4 FragColor;

        void main()
        {
            if(TexCoord[0] == TexCoord[1]) {
                // if they are the same, we are not using the texture
                FragColor = Color;
            } else {
                //FragColor = texture(Texture, TexCoord) * Color;
                vec4 sampled = vec4(1.0, 1.0, 1.0, texture(Texture, TexCoord).r);
                FragColor = Color * sampled;
            }
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

    mGeometry.CreateTextureAtlas(1000, 1000, sizeof(unsigned char));

    RVector<4> board_background = ColorIntToFloat(0xD4, 0xB8, 0x67, 0xFF);

    // we need to find the width and height of the box; adjusted for the margin
    float game_board_margin = 10.0f;
    float game_board_dimension = (mWindowProperties.height * 0.75f)< (mWindowProperties.width) ? (mWindowProperties.height * 0.75f) : mWindowProperties.width - game_board_margin;
    float window_center_x = mWindowProperties.width / 2.0f;
    float game_board_width_half = game_board_dimension / 2.0f;
    auto game_board_box_origin = RVector<3>{window_center_x - game_board_width_half, 10.0f, 0.0f};
    CreateRectangle3D(mGeometry, game_board_box_origin, board_background, game_board_dimension, game_board_dimension);

    RVector<4> game_board_square_background = ColorIntToFloat(0xDD, 0xC1, 0x71, 0xFF);

    // divide dimenion by 4 then subtract for margin right and subtract margin left / 4
    float game_square_width = (game_board_dimension / 4.0f) - 10.0f - 2.50f;

    RVector<3> game_board_square_margin_right = {10.0f + game_square_width, 0.0f, 0.0f};
    RVector<3> game_board_square_margin_bottom = {0.0f, 10.0f + game_square_width, 0.0f};
    RVector<4> BLUE = RVector<4>{0.0f, 0.0f, 1.0f, 1.0f};

    auto game_board_square_origin = game_board_box_origin + RVector<3> { 10.0f, 10.0f, 0.0f };
    for(size_t i = 0; i < 4; ++i) {
        auto going_left = game_board_square_origin;
        for(size_t j = 0; j < 4; ++j) {
            CreateRectangle3D(mGeometry, going_left, game_board_square_background, game_square_width, game_square_width);
            going_left = going_left + game_board_square_margin_right;
        }
        game_board_square_origin = game_board_square_origin + game_board_square_margin_bottom;
    }

    RVector<4> green { 0.0f, 1.0f, 0.0f, 1.0f };
    RVector<4> blue { 0.0f, 0.0f, 1.0f, 1.0f };

    auto game_board_box_end = game_board_box_origin + RVector<3>{ game_board_dimension, 0.0f, 0.0f };
    std::string TITLE_2048 = "2048";

    DrawText(mGeometry, game_board_box_origin + RVector<3> {0.0f, static_cast<float>(mWindowProperties.height) - 125.0f, 0.0f}, green, 175.0f, 75.0f, TITLE_2048, 16, mWindowProperties.width, mWindowProperties.height);

    std::string SCORE = "SCORE";

    DrawText(mGeometry, game_board_box_end + RVector<3> { -210.0f, static_cast<float>(mWindowProperties.height) - 75.0f, 0.0f}, blue, 100.0f, 50.0f, SCORE, 10, mWindowProperties.width, mWindowProperties.height);

    std::string BEST = "BEST";

    DrawText(mGeometry, game_board_box_end + RVector<3> { -100.0f, static_cast<float>(mWindowProperties.height) - 75.0f, 0.0f}, blue, 100.0f, 50.0f, BEST, 10, mWindowProperties.width, mWindowProperties.height);

    mBuffer.Init();

    size_t s = mGeometry.GetVertexSize();

    mBuffer.LoadData(reinterpret_cast<unsigned char*>(mGeometry.GetVerticesPointer()), mGeometry.GetVerticesByteSize(), mGeometry.GetIndicesPointer(), mGeometry.GetIndicesCount() * sizeof(unsigned int), GLBuffer::GLUsage::STATIC);

    /*
    unsigned char* atlas = mGeometry.GetAtlas()->GetData();
    std::fstream fout{"test.ppm", std::ios::openmode::_S_bin | std::ios::openmode::_S_out};
    fout << "P6\n" << mGeometry.GetAtlas()->GetWidth() << " " << mGeometry.GetAtlas()->GetHeight() << "\n255\n";
    for(size_t i = 0; i < mGeometry.GetAtlas()->GetWidth()* mGeometry.GetAtlas()->GetHeight(); ++i) {
        if(i < 10) std::cout << static_cast<int>(atlas[i]) << std::endl;
        fout << (unsigned char) (atlas[i]*255);
        fout << (unsigned char) 0;
        fout << (unsigned char) 0;
    }
    */

    mBuffer.LoadTextureRed(mGeometry.GetAtlas()->GetData(), mGeometry.GetAtlas()->GetWidth(), mGeometry.GetAtlas()->GetHeight());

    mBuffer.SetAttributePointer(0, 3, GLBuffer::GLDataType::FLOAT, 9 * sizeof(float), 0);
    mBuffer.SetAttributePointer(1, 4, GLBuffer::GLDataType::FLOAT, 9 * sizeof(float), reinterpret_cast<void*>(sizeof(float)*3));
    mBuffer.SetAttributePointer(2, 2, GLBuffer::GLDataType::FLOAT, 9 * sizeof(float), reinterpret_cast<void*>(sizeof(float)*7));

    CMatrix<4,4> proj = OrthographicProjection(0, mWindowProperties.width, mWindowProperties.height, 0, 1.0f, 0.0f);

    std::string projection_name = "proj";
    auto uniform = mGLProgram.GetUniform(projection_name).value();
    uniform.SetMat4fv(proj.GetData());

    return true;
}

int Game2048::Run()
{
    RVector<4> color = ColorIntToFloat(0xFA, 0xF8, 0xEF, 0xFF);

    while(!glfwWindowShouldClose(mWindow)) {
        ProcessKeyboardInput();

        glClearColor(color[0], color[1], color[2], color[3]);
        glClear(GL_COLOR_BUFFER_BIT);

        (void) mGLProgram.UseProgram();
        (void) mBuffer.BindVertexArrayObject();

        Draw();

        glfwSwapBuffers(mWindow);

        glfwWaitEventsTimeout(0.0001);
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

