#include "game_tfe/gl_buffer.h"

#include "glad/glad.h"

GLBuffer::~GLBuffer()
{
    if(mHasCreatedBuffer) { 
        glDeleteBuffers(1, &mElementBufferId);
        glDeleteBuffers(1, &mBufferId);
        glDeleteVertexArrays(1, &mVertexArrayObjectId);
    }
}

bool GLBuffer::Init()
{
    if(!mHasCreatedBuffer) {
        glGenVertexArrays(1, &mVertexArrayObjectId);
        glGenBuffers(1, &mBufferId);
        glGenBuffers(1, &mElementBufferId);
        mHasCreatedBuffer = true;
    }
    return true;
}

bool GLBuffer::LoadData(unsigned char* v_data, size_t v_data_size, unsigned int* e_data, size_t e_data_size, GLBuffer::GLUsage usage)
{
    glBindVertexArray(mVertexArrayObjectId);
    glBindBuffer(GL_ARRAY_BUFFER, mBufferId);
    switch(usage) {
        case GLUsage::STATIC:
            glBufferData(GL_ARRAY_BUFFER, v_data_size, v_data, GL_STATIC_DRAW);
            break;
        case GLUsage::DYNAMIC:
            glBufferData(GL_ARRAY_BUFFER, v_data_size, v_data, GL_DYNAMIC_DRAW);
            break;
    }

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mElementBufferId);
    switch(usage) {
        case GLUsage::STATIC:
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, e_data_size, e_data, GL_STATIC_DRAW);
            break;
        case GLUsage::DYNAMIC:
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, e_data_size, e_data, GL_DYNAMIC_DRAW);
            break;
    }

    return true;
}

bool GLBuffer::SetAttributePointer(unsigned int index, int size, GLDataType type, size_t stride, const void* offset)
{
    glBindVertexArray(mVertexArrayObjectId);
    glVertexAttribPointer(index, size, GL_FLOAT, GL_FALSE, stride, offset);
    glEnableVertexAttribArray(index);
    return true;
}

bool GLBuffer::BindVertexArrayObject()
{
    glBindVertexArray(mVertexArrayObjectId);
    return true;
}
