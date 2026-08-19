cmake_minimum_required(VERSION 3.20)

project(hello_parser LANGUAGES CXX)

add_library(toolchain INTERFACE)
target_include_directories(toolchain INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/src)
target_compile_features(toolchain INTERFACE cxx_std_20)

add_executable(parser src/main.cpp)
target_link_libraries(parser PRIVATE toolchain)

add_executable(parsertest tests/test.cpp)
target_link_libraries(parsertest PRIVATE toolchain)

enable_testing()
add_test(NAME parsertest COMMAND parsertest)
