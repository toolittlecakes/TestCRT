cmake_minimum_required(VERSION 3.12)
project(test)

set(CMAKE_CXX_STANDARD 14)



add_library(lib lib/router.h lib/coordinates.cpp lib/coordinates.h lib/board.cpp lib/board.h lib/way.cpp lib/way.h)

find_library(TaskLib lib cmake-build-debug)


add_executable(lib_tests catch2/catch.hpp lib/tests/test_framework.cpp lib/tests/test.cpp)
target_include_directories(lib_tests PRIVATE catch2)
target_include_directories(lib_tests PRIVATE lib)
target_link_libraries(lib_tests LINK_PUBLIC ${TaskLib})


add_executable(demo demo/main.cpp demo/params.cpp demo/params.h demo/demo.cpp demo/demo.h)
target_include_directories(demo PRIVATE lib)
target_link_libraries(demo LINK_PUBLIC ${TaskLib})