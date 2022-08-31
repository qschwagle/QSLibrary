#ifndef GAME_TFE_GL_SHADER_H
#define GAME_TFE_GL_SHADER_H

#include <string>

/**
 * manages a gl shader
 */
class GLShader {
public:
    /** default constructor */
    GLShader()=default;

    /** cleans up gl shader */
    ~GLShader();

    /** gl shader is not copyable */
    GLShader(const GLShader&)=delete;

    /** gl shader is not copyable */
    GLShader& operator=(const GLShader&)=delete;

    /**
     * Get the shader id
     *
     * \returns shader id
     */
    [[nodiscard]] int GetId(void) { return mId; }

    /**
     * types of shaders
     */
    enum class GLShaderType {
        /// not a shader
        NONE,

        /// vertex shader
        VERTEX,

        /// fragment shader
        FRAGMENT
    };

    /**
     * creates a shader of the provided type from the provided
     *
     * \param src shader source code
     * \param type type of shader to create
     * \returns true if successful, otherwise false
     */
    [[nodiscard]] bool InitShader(std::string& src, GLShaderType type);

    /**
     * get the shader type
     *
     * \returns the shader type
     */
    [[nodiscard]] GLShaderType GetShaderType(void) { return mShaderType; }

private:
    /// saved src for potential debugging later
    std::string mShaderSrc;

    /// the type of shader being held
    GLShaderType mShaderType{GLShaderType::NONE};

    /// has this object created a shader in the past
    bool mHasCreatedShader{false};

    /// shader id
    unsigned int mId{0};
};

#endif // GAME_TFE_GL_SHADER_H

