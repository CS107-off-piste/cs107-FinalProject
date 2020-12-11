enable_testing()
include(CTest)

include_directories(${gtest_dir}/include)
link_directories(${gtest_dir}/lib)

file(GLOB TEST_H *.h *.hpp)

file(GLOB TEST_SRC test*.cpp)

add_library(OFFPISTE_TESTS SHARED ${TEST_SRC} ${TEST_H})
if(APPLE)
  target_link_libraries(OFFPISTE_TESTS gtest gtest_main)
endif()
