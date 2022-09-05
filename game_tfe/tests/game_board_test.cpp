//
// Created by Quinton Schwagle on 9/4/22.
//

#include "gtest/gtest.h"

#include "game_tfe/game_board.h"

/**
 * helper function which zeros the board which does not normally occur in the game
 * @param board board to have all squares set to 0
 */
void ZeroBoard(GameBoard& board)
{
    for(int i = 0; i < 16; ++i) {
        board.SetSquare(i, GameSquare(0));
    }
}

TEST(GameBoard, Constructor)
{
    GameBoard board;
    int count = 0;
    for(int i = 0 ; i < 16; ++i) {
        if(board.GetGameSquare(i).GetValue() > 0)  count++;
    }
    ASSERT_EQ(count, 2);
}

TEST(GameBoardTesterHelper, ZeroBoard)
{
    GameBoard board;
    ZeroBoard(board);
    for(int i = 0; i < 16; ++i) {
        ASSERT_EQ(board.GetGameSquare(i).GetValue(), 0);
    }
}

TEST(GameBoard, SetAndGetSquare)
{
    GameBoard board;
    ZeroBoard(board);

    board.SetSquare(0, GameSquare(4));
    board.SetSquare(5, GameSquare(12));
    ASSERT_EQ(board.GetGameSquare(0).GetValue(), 4);
    ASSERT_EQ(board.GetGameSquare(5).GetValue(), 12);
}
