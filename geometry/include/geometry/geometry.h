//
// Created by Quinton Schwagle on 7/29/22.
//

#ifndef DRAWING_GEOMETRY_H
#define DRAWING_GEOMETRY_H

#include <vector>
#include <memory>
#include <cstring>
#include "linalg/rvector.h"

template<int length> 
class Geometry {
public:

    /**
     * holds a texture atlas
     */
    class TextureAtlas {
        public:
            /**
             * allocates a new texture atlas of width, height and bytes width
             * \param width width of texture
             * \param height height of texture
             * \param bytes subunit byte width 
             */
            TextureAtlas(size_t width, size_t height, size_t bytes) : mHeight {height}, mWidth{width}
            {
                mData = std::make_unique<unsigned char[]>(width*height*bytes);
                memset(mData.get(), 0, mHeight*mWidth*bytes);
            }

            /**
             * Get the width of the atlas
             * \returns width of the atlas
             */
            size_t GetWidth() const noexcept
            {
                return mWidth;
            }

            /**
             * Get the height of the atlas
             * \returns height of the atlas
             */
            size_t GetHeight() const noexcept
            {
                return mHeight;
            }

            /**
             * get the buffer pointer
             * \returns buffer pointer
             */
            unsigned char* GetData() noexcept
            {
                return mData.get();
            }

            /**
             * get the a constant pointer to the buffer
             * \returns const buffer pointer
             */
            const unsigned char * GetData() const noexcept
            {
                return mData.get();
            }
       
            /**
             * subscript operator
             * \param i id
             * \returns value at i
             */
            unsigned char& operator[](size_t i) {
                return mData[i];
            }

            /**
             * constant subscript operator
             * \param i id
             * \returns const value at i
             */
            const unsigned char& operator[](size_t i) const {
                return mData[i];
            }

            /**
             * Get the start of the next position that can fit the width and height
             * \param width required width
             * \param height required height
             * \param block_size size of the subunits over width and height
             * \param tex_coords_out output tex coords
             * \returns pointer to position or nullptr if not found
             */
            unsigned char* GetNextFit(size_t width, size_t height, size_t block_size, std::array<QS::LinAlg::RVector<2>, 4>& tex_coords_out, std::array<size_t, 2>& offset)
            {
                if(mPosY + height + 5 < mHeight) {
                    // bot left
                    tex_coords_out[0] = QS::LinAlg::RVector<2> { static_cast<float>(mPosX) / mWidth, static_cast<float>(mPosY) / mHeight };
                    // top left
                    tex_coords_out[1] = QS::LinAlg::RVector<2> { static_cast<float>(mPosX) / mWidth, static_cast<float>(mPosY+height) / mHeight };
                    // bot right
                    tex_coords_out[2] = QS::LinAlg::RVector<2> { static_cast<float>(mPosX+width) / mWidth, static_cast<float>(mPosY) / mHeight };
                    // top right
                    tex_coords_out[3] = QS::LinAlg::RVector<2> { static_cast<float>(mPosX+width) / mWidth, static_cast<float>(mPosY+height) / mHeight };
                    offset[0] = mPosX;
                    offset[1] = mPosY;
                    mPosY += height + 5;
                    return &(mData[(mPosY-height-5)*mWidth]);
                }
                return nullptr;
            }

        private:
            /// buffer
            std::unique_ptr<unsigned char[]> mData;

            /// height of the buffer
            size_t mWidth;

            /// width of the buffer
            size_t mHeight;

            /// next free x position
            size_t mPosX{50};
            /// next free y position
            size_t mPosY{50};
    };

    void CreateTextureAtlas(size_t width, size_t height, size_t bytes)
    {
        mAtlas = std::make_unique<TextureAtlas>(width, height, bytes);
    }

    /**
     * Add the Index value to the sequence of indices
     * @param index index for the vertices
     */
    void AddIndex(size_t index) noexcept
    {
        mIndices.emplace_back(index);
    }

    size_t GetIndicesCount(void) const noexcept {
        return mIndices.size();
    }

    size_t GetVerticesCount(void) const noexcept {
        return mVertices.size();
    }

    /**
     * Add the vertex to the sequence of vertices
     * @param vertex
     */
    void AddVertex(const QS::LinAlg::RVector<length> vertex) noexcept
    {
        mVertices.emplace_back(vertex);
    }

    size_t GetVertexSize(void) const noexcept {
        return length * sizeof(float);
    }

    size_t GetVerticesByteSize(void) const noexcept {
        return GetVerticesCount() * GetVertexSize();
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

    /**
     * Get a pointer to atlas
     * \returns a pointer to an atlas
     */
    TextureAtlas* GetAtlas()
    {
        return mAtlas.get();
    }

    void Clear()
    {
        mAtlas = nullptr;
        mIndices.clear();
        mVertices.clear();
    }

private:
    /// indicies
    std::vector<unsigned int> mIndices;

    /// vertices
    std::vector<QS::LinAlg::RVector<length>> mVertices;

    /// texture atlas
    std::unique_ptr<TextureAtlas> mAtlas;
};

template<int length>
void CreateRectangle3D(Geometry<length>& out, QS::LinAlg::RVector<3> translation, QS::LinAlg::RVector<4> color, float width, float height)
{
    size_t vertices_count = out.GetVerticesCount();

    out.AddVertex(QS::LinAlg::RVector<length>{translation[0], translation[1], translation[2], color[0], color[1], color[2], color[3]});
    out.AddVertex(QS::LinAlg::RVector<length>{translation[0], translation[1]+height, translation[2], color[0], color[1], color[2], color[3]});
    out.AddVertex(QS::LinAlg::RVector<length>{translation[0]+width, translation[1], translation[2], color[0], color[1], color[2], color[3]});
    out.AddVertex(QS::LinAlg::RVector<length>{translation[0]+width, translation[1]+height, translation[2], color[0], color[1], color[2], color[3]});

    // lower triangle
    out.AddIndex(vertices_count+1);
    out.AddIndex(vertices_count);
    out.AddIndex(vertices_count+2);

    // upper triangle
    out.AddIndex(vertices_count+2);
    out.AddIndex(vertices_count+3);
    out.AddIndex(vertices_count+1);
}

template<int length>
void CreateRectangle3D(
        Geometry<length>& out, 
        QS::LinAlg::RVector<3> translation,
        QS::LinAlg::RVector<4> color,
        float width, 
        float height,
        QS::LinAlg::RVector<2> tex_coords_bot_left,
        QS::LinAlg::RVector<2> tex_coords_top_left,
        QS::LinAlg::RVector<2> tex_coords_bot_right,
        QS::LinAlg::RVector<2> tex_coords_top_right
        ) 
{
    size_t vertices_count = out.GetVerticesCount();

    out.AddVertex(QS::LinAlg::RVector<length>{translation[0], translation[1], translation[2], color[0], color[1], color[2], color[3], tex_coords_bot_left[0], tex_coords_bot_left[1]});
    out.AddVertex(QS::LinAlg::RVector<length>{translation[0], translation[1]+height, translation[2], color[0], color[1], color[2], color[3], tex_coords_top_left[0], tex_coords_top_left[1]});
    out.AddVertex(QS::LinAlg::RVector<length>{translation[0]+width, translation[1], translation[2], color[0], color[1], color[2], color[3], tex_coords_bot_right[0], tex_coords_bot_right[1]});
    out.AddVertex(QS::LinAlg::RVector<length>{translation[0]+width, translation[1]+height, translation[2], color[0], color[1], color[2], color[3], tex_coords_top_right[0], tex_coords_top_right[1]});

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
