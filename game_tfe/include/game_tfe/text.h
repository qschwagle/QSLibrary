#ifndef GAME_TFE_TEXT_H
#define GAME_TFE_TEXT_H

#include <string>


#include "linalg/rvector.h"
#include "geometry/geometry.h"


/**
 * Write the string texture to out buffer and generate the vertices mapping to height and width
 * \param out out geometry buffer
 * \param coordinate translation to coordinate 
 * \param color color of text
 * \param width width of rectangle
 * \param height height of rectangle
 * \param text text to render
 * \param pt font size
 * \param screen_width width of screen in pixels
 * \param screen_height height of screen in pixels
 */
void DrawText(Geometry<9>& out, RVector<3> coordinate, RVector<4> color, float width, float height, std::string& text, unsigned int pt,
        unsigned int screen_width, unsigned int screen_height);

#endif
