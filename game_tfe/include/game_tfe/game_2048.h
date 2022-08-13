//
// Created by Quinton Schwagle on 8/13/22.
//

#ifndef DRAWING_GAME_2048_H
#define DRAWING_GAME_2048_H

#include "GLFW/glfw3.h"

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

private:

    /// glfw window
    GLFWwindow* mWindow{nullptr};

};

#endif //DRAWING_GAME_2048_H
