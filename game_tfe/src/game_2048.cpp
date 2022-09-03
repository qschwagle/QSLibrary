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
#include <cstdlib>
#include <ctime>

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

/**
 * callback registered on glfw window to respond to keyboard input
 * \param window glfw window
 * \param key keyboard key
 * \param scancode scancode
 * \param action action
 * \param mods mods
 */
static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    Game2048* game = static_cast<Game2048*>(glfwGetWindowUserPointer(window));
    game->ProcessKeyboardInput(key, scancode, action, mods);
}

/** 
 * callback registered on glfw windwo to respont to mouse input
 * \param window glfw window
 * \param 
 */
static void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{
    double xpos, ypos;
    glfwGetCursorPos(window, &xpos, &ypos);
    Game2048* game = static_cast<Game2048*>(glfwGetWindowUserPointer(window));
    if(button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
        game->LeftMouseClick(xpos, ypos);
    }
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
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

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
    glfwSetKeyCallback(mWindow, &KeyCallback);
    glfwSetMouseButtonCallback(mWindow, &MouseButtonCallback);

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
            if(TexCoord[0] == 0.0 && TexCoord[1] == 0.0) {
                // if they are the same, we are not using the texture
                FragColor = Color;
            } else {
                vec4 sampled = vec4(1.0, 1.0, 1.0, texture(Texture, TexCoord).r);
                if(sampled.a < 0.1) {
                    discard;
                }
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

    glDisable(GL_DEPTH_TEST);
    glDisable(GL_STENCIL_TEST);

    return true;
}

int Game2048::Run()
{
    RVector<4> color = ColorIntToFloat(0xFA, 0xF8, 0xEF, 0xFF);

    while(!glfwWindowShouldClose(mWindow)) {

        mGeometry.CreateTextureAtlas(1024, 1024, sizeof(unsigned char));

        RVector<4> board_background = ColorIntToFloat(0xD4, 0xB8, 0x67, 0xFF);

        // we need to find the width and height of the box; adjusted for the margin
        float game_board_margin = 10.0f;
        float game_board_dimension = (mWindowProperties.height * 0.75f)< (mWindowProperties.width) ? (mWindowProperties.height * 0.75f) : mWindowProperties.width - game_board_margin;
        float window_center_x = mWindowProperties.width / 2.0f;
        float game_board_width_half = game_board_dimension / 2.0f;
        auto game_board_box_origin = RVector<3>{window_center_x - game_board_width_half, 10.0f, -0.1f};

        RVector<4> game_board_square_background = ColorIntToFloat(0xDD, 0xC1, 0x71, 0xFF);

        // divide dimenion by 4 then subtract for margin right and subtract margin left / 4
        float game_square_width = (game_board_dimension / 4.0f) - 10.0f - 2.50f;

        RVector<3> game_board_square_margin_right = {10.0f + game_square_width, 0.0f, 0.0f};
        RVector<3> game_board_square_margin_bottom = {0.0f, 10.0f + game_square_width, 0.0f};
        RVector<4> BLUE = RVector<4>{0.0f, 0.0f, 1.0f, 1.0f};

        mBoard.Draw(mGeometry, game_board_box_origin, game_board_dimension);
        if(mGameHasEnded) {
            // display end screen
            RVector<4> TRANSPARENT_WHITE = {1.0f, 1.0f, 1.0f, 0.5f};
            RVector<4> TEXT_COLOR = {0.0f, 0.0f, 0.0f, 1.0f};
            CreateRectangle3D(mGeometry, game_board_box_origin, TRANSPARENT_WHITE, game_board_dimension, game_board_dimension);
            std::string GAME_OVER = "Game over!";
            RVector<3> mid_point = { game_board_box_origin[0] + game_board_dimension / 2.0f, game_board_box_origin[1] + game_board_dimension * 2.0f / 3.0f, -0.6f};
            
            DrawText(mGeometry, nullptr, mid_point, TEXT_COLOR, GAME_OVER, 24, 100, 100, TextAlignment::CENTER);

            RVector<3> below_mid = { game_board_box_origin[0] + game_board_dimension / 2.0f - 150.0f / 2.0f, game_board_box_origin[1] + 3.0f * game_board_dimension / 8.0f, -0.2f };

            RVector<4> BUTTON_BG_COLOR = ColorIntToFloat(0x8F, 0x7A, 0x66, 0xFF);

            RVector<4> BUTTON_TEXT_COLOR =  ColorIntToFloat(0xFA, 0xF8, 0xEF, 0xFF);
            std::string NEW_GAME = "New Game";

            mNewGameEndScreen.Draw(mGeometry, below_mid, 150.0, 50.0f, BUTTON_BG_COLOR, BUTTON_TEXT_COLOR, 14, NEW_GAME);
        }

        RVector<4> green { 0.0f, 1.0f, 0.0f, 1.0f };
        RVector<4> blue { 0.0f, 0.0f, 1.0f, 1.0f };

        float window_scale_x, window_scale_y;
        glfwGetWindowContentScale(mWindow, &window_scale_x, &window_scale_y);
        unsigned int window_scale_x_int = 100; //window_scale_x * 100;
        unsigned int window_scale_y_int = 100; // window_scale_y * 100;

        auto game_board_box_end = game_board_box_origin + RVector<3>{ game_board_dimension, 0.0f, 0.0f };
        std::string TITLE_2048 = "2048";
        // #776E65
        RVector<4> TITLE_COLOR = ColorIntToFloat(0x77, 0x6E, 0x65, 0xFF);

        DrawText(mGeometry, nullptr, game_board_box_origin + RVector<3> {0.0f, static_cast<float>(mWindowProperties.height) - 125.0f, -0.9f}, TITLE_COLOR, TITLE_2048, 48, window_scale_x_int, window_scale_y_int);

        std::string SCORE = "SCORE";

        DrawText(mGeometry, nullptr, game_board_box_end + RVector<3> { -160.0f, static_cast<float>(mWindowProperties.height) - 35.0f, -0.8f}, TITLE_COLOR, SCORE, 12, window_scale_x_int, window_scale_y_int);

        std::string current_score = std::to_string(mScore);

        DrawText(mGeometry, nullptr, game_board_box_end + RVector<3> { -160.0f, static_cast<float>(mWindowProperties.height) - 60.0f, -0.5f}, TITLE_COLOR, current_score, 22, window_scale_x_int, window_scale_y_int);

        std::string BEST = "BEST";

        DrawText(mGeometry, nullptr, game_board_box_end + RVector<3> { -50.0f, static_cast<float>(mWindowProperties.height) - 35.0f, -0.3f}, TITLE_COLOR, BEST, 12, window_scale_x_int, window_scale_y_int);

        std::string best_score = std::to_string(mBestScore);

        DrawText(mGeometry, nullptr, game_board_box_end + RVector<3> { -50.0f, static_cast<float>(mWindowProperties.height) - 60.0f, -0.2f}, TITLE_COLOR, best_score, 22, window_scale_x_int, window_scale_y_int);
        
        std::string NEW_GAME = "New Game";
        RVector<4> BUTTON_BG_COLOR = ColorIntToFloat(0x8F, 0x7A, 0x66, 0xFF);
        RVector<4> BUTTON_TEXT_COLOR =  ColorIntToFloat(0xFA, 0xF8, 0xEF, 0xFF);

        mNewGame.Draw(mGeometry, game_board_box_end + RVector<3> { -150.0f, static_cast<float>(mWindowProperties.height) - 130.0f, 0.0f }, 150.0f, 50.0f, BUTTON_BG_COLOR, BUTTON_TEXT_COLOR, 14, NEW_GAME);


        mBuffer.Init();

        size_t s = mGeometry.GetVertexSize();

        mBuffer.LoadData(reinterpret_cast<unsigned char*>(mGeometry.GetVerticesPointer()), mGeometry.GetVerticesByteSize(), mGeometry.GetIndicesPointer(), mGeometry.GetIndicesCount() * sizeof(unsigned int), GLBuffer::GLUsage::DYNAMIC);

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


        glClearColor(color[0], color[1], color[2], color[3]);
        glClear(GL_COLOR_BUFFER_BIT);

        (void) mGLProgram.UseProgram();
        (void) mBuffer.BindVertexArrayObject();

        Draw();

        mGeometry.Clear();

        glfwSwapBuffers(mWindow);

        glfwWaitEventsTimeout(0.001);
    }
    return 0;
}

int Game2048::Draw()
{
    glDrawElements(GL_TRIANGLES, mGeometry.GetIndicesCount(), GL_UNSIGNED_INT, 0);
    GLenum error;
    while((error = glGetError()) != GL_NO_ERROR) {
        switch(error) {
            case GL_INVALID_ENUM:
                std::cerr << "Draw: GL_INVALID_ENUM" << std::endl;
                break;
            case GL_INVALID_VALUE:
                std::cerr << "Draw: GL_INVALID_VALUE" << std::endl;
                break;
            case GL_INVALID_OPERATION:
                std::cerr << "Draw: GL_INVALID_OPERATION" << std::endl;
                break;
            case GL_STACK_OVERFLOW:
                std::cerr << "Draw: GL_STACK_OVERFLOW" << std::endl;
                break;
            case GL_OUT_OF_MEMORY:
                std::cerr << "Draw: GL_OUT_OF_MEMORY" << std::endl;
                break;
            case GL_INVALID_FRAMEBUFFER_OPERATION:
                std::cerr << "Draw: GL_INVALID_FRAMEBUFFER_OPERATION" << std::endl;
                break;
            default:
                std::cerr << "Draw: GL UNKNOWN ERROR" << std::endl;
        }
    }
    return 0;
}

void Game2048::ProcessKeyboardInput(int key, int scancode, int action, int mods)
{
    if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(mWindow, true);
    }

    if(!mGameHasEnded) {
        if(key ==  GLFW_KEY_W && action == GLFW_PRESS || key == GLFW_KEY_UP && action == GLFW_PRESS) {
            mScore += mBoard.Move(GameBoard::MoveDirection::UP);
        }

        if(key == GLFW_KEY_S && action == GLFW_PRESS || key == GLFW_KEY_DOWN && action == GLFW_PRESS) {
            mScore += mBoard.Move(GameBoard::MoveDirection::DOWN);
        }

        if(key == GLFW_KEY_A && action == GLFW_PRESS || key == GLFW_KEY_LEFT && action == GLFW_PRESS) {
            mScore += mBoard.Move(GameBoard::MoveDirection::LEFT);
        }

        if(key == GLFW_KEY_D && action == GLFW_PRESS || key == GLFW_KEY_RIGHT && action == GLFW_PRESS) {
            mScore += mBoard.Move(GameBoard::MoveDirection::RIGHT);
        }
        if(mScore > mBestScore) {
            mBestScore = mScore;
        }
        if(!mBoard.AvailableMove()) {
            mGameHasEnded = true;
        }
    }
}


void Game2048::LeftMouseClick(double x, double y)
{
    RVector<2> coord = { static_cast<float>(x), static_cast<float>(mWindowProperties.height - y) };
    if(mNewGame.Hit(coord)) {
        ResetGame();
    }
    if(mGameHasEnded && mNewGameEndScreen.Hit(coord)) {
        ResetGame();
    }
}

void Game2048::ResetGame()
{
    mGameHasEnded = false;
    mScore = 0;
    mBoard.Reset();
}
