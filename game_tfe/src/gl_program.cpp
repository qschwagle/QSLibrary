#include "game_tfe/gl_program.h"

#include <iostream>

#include "glad/glad.h"

GLProgram::~GLProgram()
{
    if(mProgramWasCreated) glDeleteProgram(mId);
}

void GLProgram::AddVertexShader(std::shared_ptr<GLShader> shader)
{
    mVertexShader = shader;
}



void GLProgram::AddFragmentShader(std::shared_ptr<GLShader> shader)
{
    mFragmentShader = shader;
}

bool GLProgram::CompileProgram(void)
{
    // if we have created a program in the past, we delete it and create a new program
    if(mProgramWasCreated) glDeleteProgram(mId);

    mId = glCreateProgram();

    // we have created a program at least once in the lifetime of the object
    mProgramWasCreated = true;

    glAttachShader(mId,mVertexShader->GetId());
    GLenum error = glGetError();
    if(error != GL_NO_ERROR) {
        std::cerr << "GLProgram::CompileProgram: error while attaching vertexShader" << std::endl;
        return false;
    }

    glAttachShader(mId,mFragmentShader->GetId());
    error = glGetError();
    if(error != GL_NO_ERROR) {
        std::cerr << "GLProgram::CompileProgram: error while attaching fragmentShader" << std::endl;
        return false;
    }

    glLinkProgram(mId);
    GLenum pname = GL_LINK_STATUS;
    GLint param;
    glGetProgramiv(mId, pname, &param);
    if(param == GL_FALSE) {
        std::cerr << "GLProgram::CompileProgram: error while linking program" << std::endl;
        return false;
    }

    return true;
}

bool GLProgram::UseProgram() {
    glUseProgram(mId);
    return true;
}

std::optional<GLProgram::Uniform> GLProgram::GetUniform(std::string& name)
{
    int res = glGetUniformLocation(mId, name.c_str());
    if(glGetError() != GL_NO_ERROR) {
        std::cerr << "GLProgram::GetUniform: Error attempting to get uniform: " << name << std::endl;
        return std::optional<GLProgram::Uniform>();
    } else {
        return std::optional<GLProgram::Uniform>(res);
    }
}

void GLProgram::Uniform::SetMat4fv(const float* matrix)
{
    glUniformMatrix4fv(mId, 1, GL_FALSE, matrix);
}
