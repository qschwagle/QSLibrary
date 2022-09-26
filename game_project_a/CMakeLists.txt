set(SRC_MAIN src/main.cpp)
set(SRC src/game.cpp)
set(INCLUDE_FILES include/game_project_a/game.h include/game_project_a/logger.h)

add_executable(game_project_a ${SRC_MAIN} ${SRC} ${INCLUDE_FILES})

TARGET_INCLUDE_DIRECTORIES(game_project_a PUBLIC include)

SET_PROPERTY(TARGET game_project_a PROPERTY CXX_STANDARD 20)

find_package(OpenGL REQUIRED)

target_link_libraries(game_project_a PUBLIC glfw ${OPENGL_gl_LIBRARY})