cmake_minimum_required(VERSION 3.12)
project(test)

set(CMAKE_CXX_STANDARD 14)



add_library(lib lib/router.cpp lib/router.h lib/types.h)

find_library(TaskLib lib cmake-build-debug)


add_executable(lib_tests catch2/catch.hpp lib/tests/test_framework.cpp lib/tests/test.cpp)
target_include_directories(lib_tests PRIVATE catch2)
target_include_directories(lib_tests PRIVATE lib)
target_link_libraries(lib_tests LINK_PUBLIC ${TaskLib})


add_executable(utils_tests catch2/catch.hpp demo/tests/test_framework.cpp demo/tests/test.cpp demo/utils.h demo/utils.cpp)
target_include_directories(utils_tests PRIVATE catch2)
target_include_directories(utils_tests PRIVATE lib)
target_include_directories(utils_tests PRIVATE demo)
target_link_libraries(utils_tests LINK_PUBLIC ${TaskLib})



add_executable(demo demo/main.cpp demo/utils.cpp demo/utils.h)
target_include_directories(demo PRIVATE lib)
target_link_libraries(demo LINK_PUBLIC ${TaskLib})