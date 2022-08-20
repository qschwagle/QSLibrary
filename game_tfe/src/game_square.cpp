#include "game_tfe/game_square.h"
#include "game_tfe/text.h"

static RVector<4> GREEN = { 0.0f, 1.0f, 0.0f, 1.0f};

GameSquare::GameSquare(int value) : mValue{value}
{
}

bool GameSquare::TryMerge(const GameSquare& lhs)
{
    return mValue == lhs.mValue;
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
}
