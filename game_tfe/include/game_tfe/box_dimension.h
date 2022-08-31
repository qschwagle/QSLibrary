#ifndef GAME_ETF_BOX_DIMENSIONS_H
#define GAME_ETF_BOX_DIMENSIONS_H

#include "linalg/rvector.h"

/**
 * Box Dimension
 */
struct BoxDimension {
    /// width of the box
    int width{0};
    
    /// height of the box
    int height{0};

    /// margin of the box: UP RIGHT BOTTOM LEFT
    RVector<4> margin{0, 0, 0, 0};

    /// position of the box: X, Y
    RVector<2> position{0, 0};
};

#endif //GAME_EFT_BOX_DIMENSIONS_H
