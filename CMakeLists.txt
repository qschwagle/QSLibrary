cmake_minimum_required(VERSION 3.22)
project(drawing)

add_subdirectory(geometry)

add_subdirectory(linalg)

add_subdirectory(helloworld)

add_subdirectory(cpp_scaffold)

add_subdirectory(argument_parser)

add_subdirectory(string_algorithms)

include(FetchContent)
FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG 58d77fa8070e8cec2dc1ed015d66b454c8d78850 # v1.12.1
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(googletest)

enable_testing()
