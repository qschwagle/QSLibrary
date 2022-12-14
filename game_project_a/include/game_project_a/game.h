#ifndef QSLIBRARY_GAME_PROJECT_A_GAME_H
#define QSLIBRARY_GAME_PROJECT_A_GAME_H 1

#include <memory>

#include "game_project_a/logger.h"

struct GLFWwindow;

/**
 * Game Program Class
 *
 * This program should never be inherited
 */
class Game final
{
public:
    /**
     * constructor
     */
    Game() noexcept;

    /**
     * destructor
     */
    ~Game();

    /**
     * Set the logger for the application. A default is used if not called
     * @param logger logger for application
     */
    void SetLogger(std::unique_ptr<Logger> logger) noexcept
    {
        mLogger = std::move(logger);
    }

    /**
     * initializes the game
     * @param argc number of arguments ( should be straight from main )
     * @param argv arguments ( should be straight from main
     * @return did the game object successfully initialize
     */
    [[nodiscard]] bool Init(int argc, char** argv);

    /**
     * start the game
     * @return exit status
     */
    [[nodiscard]] int Run();

private:
    /// logger used by the game
    std::unique_ptr<Logger> mLogger{std::make_unique<Logger>()};

    /// was glfw properly initialized?
    bool mGLFWInitialized{false};

    /// window handle
    GLFWwindow* mWindow{nullptr};
};


#endif // QSLIBRARY_GAME_PROJECT_A_GAME_H
