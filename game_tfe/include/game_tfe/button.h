#ifndef GAME_TFE_BUTTON_H
#define GAME_TFE_BUTTON_H 

#include <string>

#include "geometry/geometry.h"
#include "linalg/rvector.h"

/**
 * A Button that draws itself
 */
class Button {
    public:
        /**
         * Draws the box, setting the dimensions from the message dimension and padding and writes to out
         * \param out geometry out buffer
         * \param position position of the button
         * \param width width of the button 
         * \param height height of the button
         * \param bg background color
         * \param color color of text
         * \param message message to be displayed
         */
        void Draw(Geometry<9>& out, QS::LinAlg::RVector<3> position, float width, float height, QS::LinAlg::RVector<4> bg, QS::LinAlg::RVector<4> color, int pt, std::string& text);

        /**
         * checks whether the value hit the button based on the position supplied
         * \param pos position hit
         * \returns true if hit, otherwise false
         */
        bool Hit(const QS::LinAlg::RVector<2>& pos);

    private:
        /// last dimensions generated width / height of the box
        QS::LinAlg::RVector<2> mDimensions;

        /// last position drawn
        QS::LinAlg::RVector<2> mPosition;
};



#endif //GAME_TFE_BUTTON_H
