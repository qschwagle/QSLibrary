//
// Created by Quinton Schwagle on 8/13/22.
//

#ifndef DRAWING_GAME_2048_H
#define DRAWING_GAME_2048_H

#include <vector>

#include "game_tfe/gl_program.h"
#include "game_tfe/gl_buffer.h"

struct GLFWwindow;

struct WindowProperties {
    int width;
    int height;
};

/**
 *  Program class for 2048
 *
 *  manages all io and data relevant for 2048
 */
class Game2048
{
public:
    Game2048();

    virtual ~Game2048() noexcept;

    /** not copyable */
    Game2048(const Game2048&)=delete;

    /** not copyable */
    Game2048& operator=(const Game2048&)=delete;

    /** not movable */
    Game2048(const Game2048&&)=delete;

    /** not  movable */
    Game2048& operator=(const Game2048&&)=delete;

    /**
     *
     * Initializes the Program with terminal parameters
     *
     * @param argc argument count
     * @param argv argument parameters
     * @return true is successful. otherwise false
     */
    bool Init(int argc, char** argv);

    /**
     *
     * The run loop for the program
     *
     * @return exit status
     */
    int Run();

    /**
     * Draw the game
     * @return 0 for success, any other value for error
     */
    int Draw();

    /**
     * retrieves the window properties
     * \return window properties
     */
    WindowProperties& GetWindowProperties(void) noexcept {
        return mWindowProperties;
    }

private:
    void ProcessKeyboardInput(void);

    /// holds window properties
    WindowProperties mWindowProperties = {
        .width = 1280,
        .height = 720
    };

    /// glfw window
    GLFWwindow* mWindow{nullptr};

    /// gl program
    GLProgram mGLProgram;

    // gl buffer
    GLBuffer mBuffer;

    std::vector<float> mTriangle = { 0.0, 0.5f, 0.0f,
                                    -0.5, 0.0f, 0.0f,
                                    0.5, 0.0f, 0.0f };
};

#endif //DRAWING_GAME_2048_H
