cmake_minimum_required(VERSION 3.20)
project(makeBitMaps)

set(CMAKE_CXX_STANDARD 14)

add_executable(makeBitMaps main.cpp generate_font_data_array.h generate_font_data_array.cpp)
