
SET(INCLUDE_FILES include/linalg/cmatrix.h include/linalg/cvector.h include/linalg/rvector.h)

SET(SRC_FILES src/cmatrix.cpp src/cvector.cpp src/rmatrix.cpp src/rvector.cpp)

SET(TEST_FILES test/rvector_test.cpp test/rmatrix_test.cpp test/cmatrix_test.cpp test/cvector_test.cpp)

add_library(linalg ${INCLUDE_FILES} ${SRC_FILES})

set_property(TARGET linalg PROPERTY CXX_STANDARD 20)

target_include_directories(linalg PUBLIC include)

add_executable(
        linalg_test
        ${TEST_FILES}
)

set_property(TARGET linalg_test PROPERTY CXX_STANDARD 20)

target_link_libraries(linalg_test GTest::gtest_main linalg)

include(GoogleTest)

gtest_discover_tests(linalg_test)
