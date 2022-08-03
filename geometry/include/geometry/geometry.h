//
// Created by Quinton Schwagle on 7/29/22.
//

#ifndef DRAWING_GEOMETRY_H
#define DRAWING_GEOMETRY_H

#include <vector>
#include "linalg/rvector.h"

class Geometry {
public:

    /**
     * Add the Index value to the sequence of indices
     * @param index index for the vertices
     */
    void AddIndex(size_t index) noexcept;

    /**
     * Add the vertex to the sequence of vertices
     * @param vertex
     */
    void AddVertex(const RVector<3>& vertex) noexcept;

    /**
     * Get the start of a constant iterator for indices
     * @return start constant iterator for indicies
     */
    auto GetIndicesBegin() {
        return mIndices.cbegin();
    }

    /**
     * Get the end of a constant iterator for indices
     * @return end constant iterator for indicies
     */
    auto GetIndicesEnd() {
        return mIndices.cend();
    }

    /**
     * Get the start of the iterator for vertices
     * @return start iterator
     */
    auto GetVerticesBegin() {
        return mVertices.cbegin();
    }

    /**
     * Get end iterator for vertices
     * @return end iterator for vertices
     */
    auto GetVerticesEnd() {
        return mVertices.cend();
    }

private:
    /// indicies
    std::vector<size_t> mIndices;
    /// vertices
    std::vector<RVector<3>> mVertices;
};


#endif //DRAWING_GEOMETRY_H
