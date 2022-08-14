#include "game_tfe/gl_shader.h"

#include "glad/glad.h"

#include <iostream>

GLShader::~GLShader()
{
    if(mHasCreatedShader) glDeleteShader(mId);
}


bool GLShader::InitShader(std::string& src, GLShaderType type)
{
    // delete the shader if it was already created
    if(mHasCreatedShader) glDeleteShader(mId);

    switch(type) {
        case GLShaderType::FRAGMENT:
            mId = glCreateShader(GL_FRAGMENT_SHADER);
            break;
        case GLShaderType::VERTEX:
            mId = glCreateShader(GL_VERTEX_SHADER);
            break;
        case GLShaderType::NONE:
            std::cerr << "GLShader::InitShader: NONE is not an accepted shader type" << std::endl;
            return false;
    }
    mHasCreatedShader = true;

    const char* c_src = src.c_str();

    glShaderSource(mId, 1, &c_src, NULL);
    glCompileShader(mId);

    int success;
    char infoLog[512];
    glGetShaderiv(mId, GL_COMPILE_STATUS, &success);
    if(success == GL_FALSE) {
        glGetShaderInfoLog(mId, 512, NULL, infoLog);
        std::cerr << "GLShader::InitShader:Error: " << infoLog << std::endl;
        return false;
    }

    return true;
}
