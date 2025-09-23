cmake_minimum_required(VERSION 3.10)
project(MatrixCalculator VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

enable_testing()


add_library(matrix_lib STATIC src/matrix.cpp src/matrix.h)

add_executable(matrix_app src/main.cpp)
target_link_libraries(matrix_app matrix_lib)

add_executable(test_app src/test.cpp)
target_link_libraries(test_app matrix_lib)

add_test(NAME matrix_tests COMMAND test_app)