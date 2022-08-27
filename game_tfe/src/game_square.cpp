#include "game_tfe/game_square.h"

#include <string>
#include <iostream>

#include "game_tfe/text.h"

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


static RVector<4> GREEN = { 0.0f, 1.0f, 0.0f, 1.0f};
static RVector<4> BLACK = { 0.0f, 0.0f, 0.0f, 1.0f};
static RVector<4> TWO_BACKGROUND = ColorIntToFloat(0xEE, 0xE4, 0xDA, 0xFF);
static RVector<4> FOUR_BACKGROUND = ColorIntToFloat(0xEE, 0xE1, 0xC9, 0xFF);
static RVector<4> EIGHT_BACKGROUND = ColorIntToFloat(0xF3, 0xB2, 0x7A, 0xFF);
static RVector<4> SIXTEEN_BACKGROUND = ColorIntToFloat(0xF6, 0x96, 0x64, 0xFF);
static RVector<4> THIRTY_TWO_BACKGROUND = ColorIntToFloat(0xF7, 0x7C, 0x5F, 0xFF);
static RVector<4> SIXTY_FOUR_BACKGROUND = ColorIntToFloat(0xF7, 0x5F, 0x3B, 0xFF);
static RVector<4> HUNDRED_TWENTY_EIGHT_BACKGROUND = ColorIntToFloat(0xED, 0xD0, 0x73, 0xFF);
static RVector<4> TWO_FIFTY_SIX_BACKGROUND = ColorIntToFloat(0xED, 0xCC, 0x62, 0xFF);
static RVector<4> FIVE_TWELVE_BACKGROUND = ColorIntToFloat(0xED, 0xC9, 0x50, 0xFF);

GameSquare::GameSquare(int value) : mValue{value}
{
}

unsigned long long GameSquare::Merge(GameSquare& lhs)
{
    if(mValue == lhs.mValue) {
        lhs.mValue = 0;
        mValue *= 2;
        return mValue;
    } else {
        return 0;
    }
}

bool GameSquare::CanMerge(const GameSquare& lhs)
{
    return mValue == lhs.mValue;
}

void GameSquare::Draw(Geometry<9>& out, float width)
{

    RVector<3> pos = { mPosition[0], mPosition[1], -0.5f};
    RVector<3> mid_point = { mPosition[0] + width / 2.0f, mPosition[1] + width / 2.0f, -0.7f };
    std::string val_str = std::to_string(mValue);
    switch(mValue) {
        case 512:
            CreateRectangle3D(out, pos, FIVE_TWELVE_BACKGROUND, width, width);
            break;
        case 256:
            CreateRectangle3D(out, pos, TWO_FIFTY_SIX_BACKGROUND, width, width);
            break;
        case 128:
            CreateRectangle3D(out, pos, HUNDRED_TWENTY_EIGHT_BACKGROUND, width, width);
            break;
        case 64:
            CreateRectangle3D(out, pos, SIXTY_FOUR_BACKGROUND, width, width);
            break;
        case 32:
            CreateRectangle3D(out, pos, THIRTY_TWO_BACKGROUND, width, width);
            break;
        case 16:
            CreateRectangle3D(out, pos, SIXTEEN_BACKGROUND, width, width);
            break;
        case 8:
            CreateRectangle3D(out, pos, EIGHT_BACKGROUND, width, width);
            break;
        case 4:
            CreateRectangle3D(out, pos, FOUR_BACKGROUND, width, width);
            break;
        case 2:
        default:
            CreateRectangle3D(out, pos, TWO_BACKGROUND, width, width);
            break;
        case 0:
            return;
    }

    DrawText(out, nullptr, mid_point, BLACK, val_str, 14, 100, 100, TextAlignment::CENTER);
}
