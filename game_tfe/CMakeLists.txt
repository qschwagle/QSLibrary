SET(INCLUDE_FILES)
SET(SRC src/main.cpp)

add_executable(game_tfe ${SRC} ${INCLUDE_FILES})

set_property(TARGET game_tfe PROPERTY CXX_STANDARD 20)

target_link_libraries(game_tfe PRIVATE linalg geometry glfw)
