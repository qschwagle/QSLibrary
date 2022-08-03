
SET(INCLUDE_FILES include/geometry/geometry.h)

SET(SRC_FILES src/geometry.cpp)

add_library(geometry ${INCLUDE_FILES} ${SRC_FILES})

set_property(TARGET geometry PROPERTY CXX_STANDARD 20)

set_target_properties(geometry PROPERTIES LINKER_LANGUAGE CXX)

target_link_libraries(geometry PUBLIC linalg)

target_include_directories(geometry PUBLIC include)

