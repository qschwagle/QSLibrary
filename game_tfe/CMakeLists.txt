SET(INCLUDE_FILES include/game_tfe/game_2048.h include/game_tfe/gl_program.h include/game_tfe/gl_shader.h include/game_tfe/gl_buffer.h include/game_tfe/text.h include/game_tfe/game_square.h include/game_tfe/game_board.h include/game_tfe/button.h)

SET(SRC src/main.cpp src/game_2048.cpp glad/src/glad.c src/gl_program.cpp src/gl_shader.cpp src/gl_buffer.cpp src/text.cpp src/game_square.cpp src/game_board.cpp src/button.cpp)

add_executable(game_tfe ${SRC} ${INCLUDE_FILES})

set_property(TARGET game_tfe PROPERTY CXX_STANDARD 20)

find_package(OpenGL REQUIRED)

target_link_libraries(game_tfe PRIVATE linalg geometry glfw freetype ${OPENGL_gl_LIBRARY})

TARGET_INCLUDE_DIRECTORIES(game_tfe PRIVATE include glad/include)
