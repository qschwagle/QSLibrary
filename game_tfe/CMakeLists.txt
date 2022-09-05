SET(INCLUDE_FILES include/game_tfe/game_2048.h include/game_tfe/gl_program.h include/game_tfe/gl_shader.h include/game_tfe/gl_buffer.h include/game_tfe/text.h include/game_tfe/game_square.h include/game_tfe/game_board.h include/game_tfe/button.h)

SET(SRC_MAIN src/main.cpp)

SET(SRC src/game_2048.cpp glad/src/glad.c src/gl_program.cpp src/gl_shader.cpp src/gl_buffer.cpp src/text.cpp src/game_square.cpp src/game_board.cpp src/button.cpp)

add_executable(game_tfe ${SRC_MAIN} ${SRC} ${INCLUDE_FILES})

set_property(TARGET game_tfe PROPERTY CXX_STANDARD 20)

find_package(OpenGL REQUIRED)

target_link_libraries(game_tfe PRIVATE linalg geometry glfw freetype ${OPENGL_gl_LIBRARY})

TARGET_INCLUDE_DIRECTORIES(game_tfe PRIVATE include glad/include)


SET(TEST_FILES tests/game_board_test.cpp)


add_executable(game_tfe_test
        ${TEST_FILES}
        ${SRC}
)

TARGET_INCLUDE_DIRECTORIES(game_tfe_test PRIVATE include glad/include)

set_property(TARGET game_tfe_test PROPERTY CXX_STANDARD 20)

target_link_libraries(game_tfe_test GTest::gtest_main linalg geometry glfw freetype ${OPENGL_gl_LIBRARY})

include(GoogleTest)

gtest_discover_tests(game_tfe_test)
