#pragma once

#include <memory>
#include "game_tfe/gl_shader.h"

/**
 * Holds a handle to a gl program
 */
class GLProgram {
    public:

    /**
     * default constructor
     */
    GLProgram()=default;

    /**
     * Deconstructor
     *
     * deletes the program
     */
    ~GLProgram();

    /** gl program is not copyable */
    GLProgram(const GLProgram&)=delete;

    /** gl program is not copyable */
    GLProgram& operator=(const GLProgram&)=delete;

    /**
     * Add the vertex shader to the program
     *
     * Note: Maintains a shared_ptr to the vertex shader
     *
     * \param shader fragment shader
     */
    void AddVertexShader(std::shared_ptr<GLShader> shader);

    /**
     * Add the fragment shader to the program.
     *
     * Note: Maintains a shared_ptr to the fragment shader
     *
     * \param shader vertex shader
     */
    void AddFragmentShader(std::shared_ptr<GLShader> shader);

    /**
     * compile the gl program
     */
    [[nodiscard]] bool CompileProgram(void);

    /**
     * Get the program id
     * \returns program id
     */
    [[nodiscard]] int GetProgramId(void) { return mId; }

    /**
     * attempts to use the current program
     *
     * \returns true if successful, false otherwise
     */
    [[nodiscard]] bool UseProgram(void); 

    private:

    bool mProgramWasCreated{false};

    /// program id
    unsigned int mId{0};

    /// vertex shader loaded in the program
    std::shared_ptr<GLShader> mVertexShader;

    /// fragment shader loaded in the program
    std::shared_ptr<GLShader> mFragmentShader;
};
