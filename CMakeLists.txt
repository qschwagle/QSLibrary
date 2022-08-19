cmake_minimum_required(VERSION 3.22)
project(drawing)

add_subdirectory(geometry)

add_subdirectory(linalg)

add_subdirectory(helloworld)

add_subdirectory(cpp_scaffold)

add_subdirectory(game_tfe)

include(FetchContent)
FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG 58d77fa8070e8cec2dc1ed015d66b454c8d78850 # v1.12.1
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(googletest)

enable_testing()

FetchContent_Declare(
        glfw
        GIT_REPOSITORY https://github.com/glfw/glfw.git
        GIT_TAG 7482de6071d21db77a7236155da44c172a7f6c9e
)

FetchContent_MakeAvailable(glfw)

FetchContent_Declare(
    freetype
    GIT_REPOSITORY https://github.com/freetype/freetype.git
    GIT_TAG e8ebfe988b5f57bfb9a3ecb13c70d9791bce9ecf
)

FetchContent_MakeAvailable(freetype)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
