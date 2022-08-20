#include "game_tfe/game_square.h"

#include <string>
#include <iostream>

#include "game_tfe/text.h"


static RVector<4> GREEN = { 0.0f, 1.0f, 0.0f, 1.0f};
static RVector<4> BLACK = { 0.0f, 0.0f, 0.0f, 1.0f};

GameSquare::GameSquare(int value) : mValue{value}
{
}

bool GameSquare::TryMerge(GameSquare& lhs)
{
    if(mValue == lhs.mValue) {
        lhs.mValue = 0;
        mValue *= 2;
        return true;
    } else {
        return false;
    }
}

bool GameSquare::CanMerge(const GameSquare& lhs)
{
    return mValue == lhs.mValue;
}

void GameSquare::Draw(Geometry<9>& out, float width)
{
    if(mValue == 0) {
        return;
    }
    RVector<3> pos = { mPosition[0], mPosition[1], 0.0f };
    CreateRectangle3D(out, pos, GREEN, width, width);
    RVector<3> mid_point = { mPosition[0] + width / 2.0f, mPosition[1] + width / 2.0f, 0.0f };
    std::string val_str = std::to_string(mValue);
    DrawText(out, nullptr, mid_point, BLACK, val_str, 14, 100, 100, TextAlignment::CENTER);
}
