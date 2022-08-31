#ifndef GAME_TFE_TEXT_H
#define GAME_TFE_TEXT_H

#include <string>

#include "linalg/rvector.h"
#include "geometry/geometry.h"

/**
 * Write the string texture to buffer, generates vertices based around text size, and optionally writes the size to dim_out
 * \param out geometry buffer
 * \param dim_out dimensions of the resulting vertices. if nullptr, will ignore it
 * \param coordinate translation coordinates
 * \param color color of text
 * \param text text to be written
 * \param pt point font size
 */
void DrawText(Geometry<9>& out, RVector<2>* dim_out, RVector<3> coordinate, RVector<4> color, std::string& text, unsigned int pt, unsigned int screen_width, unsigned int screen_height);

/**
 * Text alignment setting
 */
enum class TextAlignment
{
    /// center alignment
    CENTER,

    /// left alignment
    LEFT
};

/**
 * Write the string texture to buffer, generates vertices based around text size, and optionally writes the size to dim_out. 
 * Uses text alignment to align based on coordinate
 *
 * based on psuedo code in the FreeType Tutorial. Modified for the requirements of the function
 *
 * \param out geometry buffer
 * \param dim_out dimensions of the resulting vertices. if nullptr, will ignore it
 * \param coordinate translation coordinates
 * \param color color of text
 * \param text text to be written
 * \param pt point font size
 * \param alignment text alignment
 */
void DrawText(Geometry<9>& out, RVector<2>* dim_out, RVector<3> coordinate, RVector<4> color, std::string& text, unsigned int pt, unsigned int screen_width, unsigned int screen_height, TextAlignment alignment);

#endif // GAME_TFE_TEXT_H
