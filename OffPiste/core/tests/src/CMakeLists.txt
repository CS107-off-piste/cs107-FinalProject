enable_testing()
include(CTest)

include_directories(${gtest_dir}/include)
link_directories(${gtest_dir}/lib)

file(GLOB TEST_H *.h *.hpp)

set(TEST_SRC
    test_operators.cpp
)

add_library(OFFPISTE_OPERATORS_TESTS SHARED ${TEST_SRC} ${TEST_H})
if(APPLE)
  target_link_libraries(OFFPISTE_OPERATORS_TESTS gtest gtest_main)
endif()
