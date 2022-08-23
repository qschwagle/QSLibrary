#include "game_tfe/button.h"

#include "game_tfe/text.h"

void Button::Draw(Geometry<9>& out, RVector<3> position, float width, float height, RVector<4> bg, RVector<4> color, int pt, std::string& text)
{
    mDimensions = { width, height };
    mPosition = { position[0], position[1] };
    CreateRectangle3D(out, position, bg, width, height);
    RVector<3> mid_point = { position[0] + width / 2.0f, position[1] + height / 2.0f, 0.0f };
    DrawText(out, nullptr, mid_point, color, text, pt, 100, 100, TextAlignment::CENTER);
}


bool Button::Hit(const RVector<2>& pos)
{
    return (mPosition[0] <= pos[0] && pos[0] < mPosition[0] + mDimensions[0]
            && mPosition[1] <= pos[1] && pos[1] < mPosition[1] + mDimensions[1]);
}
