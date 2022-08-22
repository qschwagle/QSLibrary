#ifndef GAME_TFE_GAME_BOARD_H
#define GAME_TFE_GAME_BOARD_H

#include "game_tfe/game_square.h"
#include "geometry/geometry.h"

/**
 * GameBoard
 */
class GameBoard {
    public:
        GameBoard();
        ~GameBoard() {}

        void Draw(Geometry<9>& out, RVector<3> position, float width);

        enum class MoveDirection {
            LEFT,
            RIGHT,
            UP, 
            DOWN
        };

        unsigned long long Move(MoveDirection m);

        void AddNewSquare(void);

    private:

        std::array<GameSquare, 16> mGameSquares;
};

#endif
