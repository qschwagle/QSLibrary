#ifndef GAME_ETF_BOX_DIMENSIONS_H
#define GAME_ETF_BOX_DIMENSIONS_H

#include "linalg/rvector.h"

/**
 * Box Dimension
 */
struct BoxDimension {
    int width{0};
    int height{0};
    RVector<4> margin{0, 0, 0, 0};
    RVector<2> position{0, 0};
};

#endif //GAME_EFT_BOX_DIMENSIONS_H
