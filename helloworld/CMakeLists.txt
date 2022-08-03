
add_executable(helloworld src/main.cpp)

set_property(TARGET helloworld PROPERTY CXX_STANDARD 20)

target_include_directories(helloworld PUBLIC include)
