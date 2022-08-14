SET(INCLUDE_FILES include/game_tfe/game_2048.h)

SET(SRC src/main.cpp src/game_2048.cpp glad/src/glad.c)

add_executable(game_tfe ${SRC} ${INCLUDE_FILES})

set_property(TARGET game_tfe PROPERTY CXX_STANDARD 20)

target_link_libraries(game_tfe PRIVATE linalg geometry glfw GL)

TARGET_INCLUDE_DIRECTORIES(game_tfe PRIVATE include glad/include)
