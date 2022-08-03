//
// Created by Quinton Schwagle on 7/29/22.
//

#include "geometry/geometry.h"


void Geometry::AddIndex(size_t index) noexcept {
    mIndices.emplace_back(index);
}

void Geometry::AddVertex(const RVector<3> &vertex) noexcept {
    mVertices.emplace_back(vertex);
}
