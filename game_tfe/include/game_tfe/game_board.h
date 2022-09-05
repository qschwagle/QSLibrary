#ifndef GAME_TFE_GAME_BOARD_H
#define GAME_TFE_GAME_BOARD_H

#include "game_tfe/game_square.h"
#include "geometry/geometry.h"

/**
 * GameBoard
 */
class GameBoard {
    public:
        /** initializes the board with two squares */
        GameBoard();
        /** deconstructor */
        ~GameBoard() {}

        /**
         * draws the game board
         * \param out geometry buffer
         * \param position position of the board\
         * \param width width the board should be
         */
        void Draw(Geometry<9>& out, QS::LinAlg::RVector<3> position, float width);

        /**
         * movement directions applied to the board
         */
        enum class MoveDirection {
            LEFT,
            RIGHT,
            UP, 
            DOWN
        };

        /**
         * tries to move in the direction provided
         * \param m direction
         * \returns new points generated due to move
         */
        unsigned long long Move(MoveDirection m);

        /**
         * checks all directions for an available move
         * \returns false if none exist, otherwise true
         */
        bool AvailableMove(void);

        /**
         * adds a new square to an open square
         */
        void AddNewSquare(void);

        void Reset();
    private:
        /// squares
        std::array<GameSquare, 16> mGameSquares;
};

#endif //GAME_TFE_GAME_BOARD_H
