cmake_minimum_required(VERSION 3.10)

project(AsciiArtGenerator VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(ascii_generator src/main.cpp)

target_include_directories(ascii_generator PRIVATE src)