#ifndef GAME_TFE_GL_BUFFER_H
#define GAME_TFE_GL_BUFFER_H

#include <cstddef>

/**
 * handles gl buffer 
 */
class GLBuffer {
public:
    /** default constructor */
    GLBuffer()=default;

    /** gl buffer is not copyable */
    GLBuffer(const GLBuffer&)=delete;

    /** gl buffer is not copyable */
    GLBuffer& operator=(const GLBuffer&)=delete;

    /** destructor */
    ~GLBuffer();

    /**
     * GL Buffer usage types
     */
    enum class GLUsage {
        STATIC,
        DYNAMIC
    };

    /**
     * data type
     */
    enum class GLDataType {
        FLOAT
    };

    /**
     * Initializes the buffer
     *
     * \returns true if initialized, otherwise false
     */
    bool Init();

    /**
     * loads data pointer to data into buffer with the provided usage
     *
     * \param v_data vertex data
     * \param v_data_size vertex data size
     * \param e_data element indicies data
     * \param e_data_size indicies size
     * \param usage usage
     * \returns true if successful, false otherwise
     */
    bool LoadData(unsigned char* v_data, size_t v_data_size, unsigned int* e_data, size_t e_data_size, GLUsage usage);

    /**
     * Sets the attrib pointer
     *
     * \param index vertex attrib to be modified
     * \param size size of the components of the vertex attrib
     * \param type type of data for each component
     * \param stride byte offset to next vertex attrib
     * \param offset pointer to first component
     */
    bool SetAttributePointer(unsigned int index, int size, GLDataType type, size_t stride, const void* offset);

    /**
     * gl binds the vertex array 
     *
     * \returns true if successful, false otherwise
     */
    bool BindVertexArrayObject();

    /**
     * Load an RGB Texture into buffer
     */
    void LoadTextureRGB(unsigned char* texture_data, int width, int height);

    /**
     * Load a single byte Texture into buffer
     */
    void LoadTextureRed(unsigned char* texture_data, int width, int height);

private:

    /// has created buffer
    bool mHasCreatedBuffer{false};

    /// has generated Texture
    bool mHasGenTexture{false};

    /// buffer id
    unsigned int mBufferId{0};

    /// element buffer id
    unsigned int mElementBufferId{0};

    /// Vertex Array Object id
    unsigned int mVertexArrayObjectId{0};

    /// texture id
    unsigned int mTextureId{0};
};

#endif // GAME_TFE_GL_BUFFER_H

