//
// Created by Quinton Schwagle on 7/29/22.
//

#ifndef DRAWING_GEOMETRY_H
#define DRAWING_GEOMETRY_H

#include <vector>
#include "linalg/rvector.h"

template<int length> 
class Geometry {
public:

    /**
     * Add the Index value to the sequence of indices
     * @param index index for the vertices
     */
    void AddIndex(size_t index) noexcept
    {
        mIndices.emplace_back(index);
    }

    size_t GetIndicesCount(void) noexcept {
        return mIndices.size();
    }

    size_t GetVerticesCount(void) noexcept {
        return mVertices.size();
    }

    /**
     * Add the vertex to the sequence of vertices
     * @param vertex
     */
    void AddVertex(const RVector<length> vertex) noexcept 
    {
        mVertices.emplace_back(vertex);
    }

    /**
     * Get the start of a constant iterator for indices
     * @return start constant iterator for indicies
     */
    auto GetIndicesBegin()
    {
        return mIndices.cbegin();
    }

    /**
     * Get the end of a constant iterator for indices
     * @return end constant iterator for indicies
     */
    auto GetIndicesEnd()
    {
        return mIndices.cend();
    }

    /**
     * Get the start of the iterator for vertices
     * @return start iterator
     */
    auto GetVerticesBegin()
    {
        return mVertices.cbegin();
    }

    /**
     * Get end iterator for vertices
     * @return end iterator for vertices
     */
    auto GetVerticesEnd()
    {
        return mVertices.cend();
    }

    float* GetVerticesPointer() 
    {
        return mVertices.data()->GetData();
    }

    unsigned int* GetIndicesPointer()
    {
        return &(mIndices.data()[0]);
    }

private:
    /// indicies
    std::vector<unsigned int> mIndices;
    /// vertices
    std::vector<RVector<length>> mVertices;
};

template<int length>
void CreateRectangle3D(Geometry<length>& out, RVector<3> translation, RVector<4> color, float width, float height)
{
    size_t vertices_count = out.GetVerticesCount();

    out.AddVertex(RVector<length>{translation[0], translation[1], translation[2], color[0], color[1], color[2], color[3]});
    out.AddVertex(RVector<length>{translation[0], translation[1]+height, translation[2], color[0], color[1], color[2], color[3]});
    out.AddVertex(RVector<length>{translation[0]+width, translation[1], translation[2], color[0], color[1], color[2], color[3]});
    out.AddVertex(RVector<length>{translation[0]+width, translation[1]+height, translation[2], color[0], color[1], color[2], color[3]});

    // lower triangle
    out.AddIndex(vertices_count+1);
    out.AddIndex(vertices_count);
    out.AddIndex(vertices_count+2);

    // upper triangle
    out.AddIndex(vertices_count+2);
    out.AddIndex(vertices_count+3);
    out.AddIndex(vertices_count+1);

}

#endif //DRAWING_GEOMETRY_H
