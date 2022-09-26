#ifndef QSLIBRARY_GAME_PROJECT_A_GAME_H
#define QSLIBRARY_GAME_PROJECT_A_GAME_H 1

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
    Game()=default;

    /**
     * initializes the game
     * @param argc number of arguments ( should be straight from main )
     * @param argv arguments ( should be straight from main
     * @return did the game object successfully initialize
     */
    bool Init(int argc, char** argv);

    /**
     * start the game
     * @return exit status
     */
    int Run();
};


#endif // QSLIBRARY_GAME_PROJECT_A_GAME_H
