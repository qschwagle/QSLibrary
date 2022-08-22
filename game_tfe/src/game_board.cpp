#include "game_tfe/game_board.h"

#include <ctime>
#include <cstdlib>


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

GameBoard::GameBoard()
{
    std::srand(std::time(0));
    int rand_1 = std::rand() % 16;
    int rand_2;
    while((rand_2 = std::rand() % 16) == rand_1);
    mGameSquares[rand_1] = std::move(GameSquare(2));
    mGameSquares[rand_2] = std::move(GameSquare(2));
}


void GameBoard::Draw(Geometry<9>& out, RVector<3> position, float width)
{

    RVector<4> board_background = ColorIntToFloat(0xD4, 0xB8, 0x67, 0xFF);
    CreateRectangle3D(out, position, board_background, width, width);
    RVector<4> game_board_square_background = ColorIntToFloat(0xDD, 0xC1, 0x71, 0xFF);
    float game_board_margin = 10.0f;

    float game_square_width = (width / 4.0f) - 10.0f - 2.50f;
    RVector<3> game_board_square_margin_right = {10.0f + game_square_width, 0.0f, 0.0f};
    RVector<3> game_board_square_margin_bottom = {0.0f, 10.0f + game_square_width, 0.0f};

    position = position + RVector<3> { 10.0f, 10.0f, 0.0f };
    for(size_t i = 0; i < 4; ++i) {
        auto going_left = position;
        for(size_t j = 0; j < 4; ++j) {
            CreateRectangle3D(out, going_left, game_board_square_background, game_square_width, game_square_width);
            mGameSquares[i*4+j].SetPosition(RVector<2> {going_left[0], going_left[1]});
            mGameSquares[i*4+j].Draw(out, game_square_width);
            going_left = going_left + game_board_square_margin_right;
        }
        position = position + game_board_square_margin_bottom;
    }
}

void GameBoard::AddNewSquare(void)
{
    auto square = GameSquare(2);
    int loc;

    // get a square that returns that it should be skipped
    while(!mGameSquares[(loc = rand() % 16)].Skip());
    mGameSquares[loc] = std::move(square);
}

static bool SkipSquare(std::array<GameSquare, 16>& board, size_t col, size_t row)
{
    return board[row * 4 + col].Skip();
}

unsigned long long GameBoard::Move(GameBoard::MoveDirection m)
{
    bool move_occurred =  false;
    unsigned long long points = 0;
    std::array<bool, 16> merged_squares;
    for(auto& i: merged_squares) {
        i = false;
    }
    switch(m) {
        case GameBoard::MoveDirection::UP:
            for(int i = 0; i < 4; ++i) {
                for(int j = 2; j > -1; --j) {
                    // we are not moving skippable squares
                    if(SkipSquare(mGameSquares, i, j)) continue;

                    int k = j+1;

                    // find the next non skippable square or the end
                    for(; k < 4 && mGameSquares[k*4+i].Skip(); ++k);

                    if(k == 4) {
                        if(k-1 != j) {
                            // we managed to get to the end and the previous square is not itself and skippable
                            mGameSquares[(k-1)*4+i] = std::move(mGameSquares[j*4+i]);
                            mGameSquares[j*4+i] = GameSquare(0);
                            move_occurred = true;
                        }
                    } else {
                        // we found a non skippable square
                        if(!merged_squares[k*4+i] && mGameSquares[k*4 + i].CanMerge(mGameSquares[j*4 +i])) {
                            // merge with it if we can
                            points += mGameSquares[k*4+i].Merge(mGameSquares[j*4+i]);
                            merged_squares[k*4+i] = true;
                            move_occurred = true;
                        } else {
                            // check to see if there is a free square right before it and its not itself
                            if(mGameSquares[(k-1)*4+i].Skip() && k-1 != j) {
                                mGameSquares[(k-1)*4+i] = std::move(mGameSquares[j*4+i]);
                                mGameSquares[j*4+i] = GameSquare(0);
                                move_occurred = true;
                            }
                        }
                    }
                }
            }
            break;
        case GameBoard::MoveDirection::DOWN:
            for(int i = 0; i < 4; ++i) {
                for(int j = 0; j < 4; ++j) {
                    // we are not moving skippable squares
                    if(SkipSquare(mGameSquares, i, j)) continue;

                    int k = j-1;

                    // find the next non skippable square or the end
                    for(; k > -1 && mGameSquares[k*4+i].Skip(); --k);

                    if(k == -1) {
                        if(k+1 != j) {
                            // we managed to get to the end and the previous square is not itself and skippable
                            mGameSquares[(k+1)*4+i] = std::move(mGameSquares[j*4+i]);
                            mGameSquares[j*4+i] = GameSquare(0);
                            move_occurred = true;
                       }
                    } else {
                        // we found a non skippable square
                        if(!merged_squares[k*4+i] && mGameSquares[k*4 + i].CanMerge(mGameSquares[j*4 +i])) {
                            // merge with it if we can
                            points += mGameSquares[k*4+i].Merge(mGameSquares[j*4+i]);
                            merged_squares[k*4+i] = true;
                            move_occurred = true;
                        } else {
                            // check to see if there is a free square right before it and its not itself
                            if(mGameSquares[(k+1)*4+i].Skip() && k+1 != j) {
                                mGameSquares[(k+1)*4+i] = std::move(mGameSquares[j*4+i]);
                                mGameSquares[j*4+i] = GameSquare(0);
                                move_occurred = true;
                            }
                        }
                    }
                }
            }
            break;
        case GameBoard::MoveDirection::LEFT:
            for(int i = 0; i < 4; ++i) {
                for(int j = 0; j < 4; ++j) {
                    // we are not moving skippable squares
                    if(SkipSquare(mGameSquares, j, i)) continue;

                    int k = j-1;

                    // find the next non skippable square or the end
                    for(; k > -1 && mGameSquares[i*4+k].Skip(); --k);

                    if(k == -1) {
                        if(k+1 != j) {
                            // we managed to get to the end and the previous square is not itself and skippable
                            mGameSquares[i*4+k+1] = std::move(mGameSquares[i*4+j]);
                            mGameSquares[i*4+j] = GameSquare(0);
                            move_occurred = true;
                       }
                    } else {
                        // we found a non skippable square
                        if(!merged_squares[i*4+k] && mGameSquares[i*4 + k].CanMerge(mGameSquares[i*4 +j])) {
                            // merge with it if we can
                            points += mGameSquares[i*4+k].Merge(mGameSquares[i*4+j]);
                            merged_squares[i*4+k] = true;
                            move_occurred = true;
                        } else {
                            // check to see if there is a free square right before it and its not itself
                            if(mGameSquares[i*4+k+1].Skip() && k+1 != j) {
                                mGameSquares[i*4+k+1] = std::move(mGameSquares[i*4+j]);
                                mGameSquares[i*4+j] = GameSquare(0);
                                move_occurred = true;
                            }
                        }
                    }
                }
            }
            break;
        case GameBoard::MoveDirection::RIGHT:
            for(int i = 0; i < 4; ++i) {
                for(int j = 3; j > -1; --j) {
                    // we are not moving skippable squares
                    if(SkipSquare(mGameSquares, j, i)) continue;

                    int k = j+1;

                    // find the next non skippable square or the end
                    for(; k < 4 && mGameSquares[i*4+k].Skip(); ++k);

                    if(k == 4) {
                        if(k-1 != j) {
                            // we managed to get to the end and the previous square is not itself and skippable
                            mGameSquares[i*4+k-1] = std::move(mGameSquares[i*4+j]);
                            mGameSquares[i*4+j] = GameSquare(0);
                            move_occurred = true;
                       }
                    } else {
                        // we found a non skippable square
                        if(!merged_squares[i*4+k] && mGameSquares[i*4 + k].CanMerge(mGameSquares[i*4 +j])) {
                            // merge with it if we can
                            points += mGameSquares[i*4+k].Merge(mGameSquares[i*4+j]);
                            merged_squares[i*4+k] = true;
                            move_occurred = true;
                        } else {
                            // check to see if there is a free square right before it and its not itself
                            if(mGameSquares[i*4+k-1].Skip() && k-1 != j) {
                                mGameSquares[i*4+k-1] = std::move(mGameSquares[i*4+j]);
                                mGameSquares[i*4+j] = GameSquare(0);
                                move_occurred = true;
                            }
                        }
                    }
                }
            }
            break;
    }
    if(move_occurred) {
        AddNewSquare();
    }
    return points;
}

bool GameBoard::AvailableMove()
{
    // up 
    for(int i = 0; i < 4; ++i) {
        for(int j = 2; j > -1; --j) {
            // we are not moving skippable squares
            if(SkipSquare(mGameSquares, i, j)) continue;

            int k = j+1;

            // find the next non skippable square or the end
            for(; k < 4 && mGameSquares[k*4+i].Skip(); ++k);

            if(k == 4) {
                if(k-1 != j) {
                    // we managed to get to the end and the previous square is not itself and skippable
                    return true;
                }
            } else {
                // we found a non skippable square
                if(mGameSquares[k*4 + i].CanMerge(mGameSquares[j*4 +i])) {
                    // merge with it if we can
                    return true;
                } else {
                    // check to see if there is a free square right before it and its not itself
                    if(mGameSquares[(k-1)*4+i].Skip() && k-1 != j) {
                        return true;
                    }
                }
            }
        }
    }
    // down
    for(int i = 0; i < 4; ++i) {
        for(int j = 0; j < 4; ++j) {
            // we are not moving skippable squares
            if(SkipSquare(mGameSquares, i, j)) continue;

            int k = j-1;

            // find the next non skippable square or the end
            for(; k > -1 && mGameSquares[k*4+i].Skip(); --k);

            if(k == -1) {
                if(k+1 != j) {
                    // we managed to get to the end and the previous square is not itself and skippable
                    return true;
               }
            } else {
                // we found a non skippable square
                if(mGameSquares[k*4 + i].CanMerge(mGameSquares[j*4 +i])) {
                    // merge with it if we can
                    return true;
                } else {
                    // check to see if there is a free square right before it and its not itself
                    if(mGameSquares[(k+1)*4+i].Skip() && k+1 != j) {
                        return true;
                    }
                }
            }
        }
    }
    // left
    for(int i = 0; i < 4; ++i) {
        for(int j = 0; j < 4; ++j) {
            // we are not moving skippable squares
            if(SkipSquare(mGameSquares, j, i)) continue;

            int k = j-1;

            // find the next non skippable square or the end
            for(; k > -1 && mGameSquares[i*4+k].Skip(); --k);

            if(k == -1) {
                if(k+1 != j) {
                    // we managed to get to the end and the previous square is not itself and skippable
                    return true;
               }
            } else {
                // we found a non skippable square
                if(mGameSquares[i*4 + k].CanMerge(mGameSquares[i*4 +j])) {
                    // merge with it if we can
                    return true;
                } else {
                    // check to see if there is a free square right before it and its not itself
                    if(mGameSquares[i*4+k+1].Skip() && k+1 != j) {
                        return true;
                    }
                }
            }
        }
    }

    // right
    for(int i = 0; i < 4; ++i) {
        for(int j = 3; j > -1; --j) {
            // we are not moving skippable squares
            if(SkipSquare(mGameSquares, j, i)) continue;

            int k = j+1;

            // find the next non skippable square or the end
            for(; k < 4 && mGameSquares[i*4+k].Skip(); ++k);

            if(k == 4) {
                if(k-1 != j) {
                    // we managed to get to the end and the previous square is not itself and skippable
                    return true;
               }
            } else {
                // we found a non skippable square
                if(mGameSquares[i*4 + k].CanMerge(mGameSquares[i*4 +j])) {
                    // merge with it if we can
                    return true;
                } else {
                    // check to see if there is a free square right before it and its not itself
                    if(mGameSquares[i*4+k-1].Skip() && k-1 != j) {
                        return true;
                    }
                }
            }
        }
    }
    return false;
}
