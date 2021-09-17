cmake_minimum_required(VERSION 3.20)
project(fontDataArray)

set(CMAKE_CXX_STANDARD 14)

add_executable(
        fontDataArray
        main.cpp
        generate_font_data_array.cpp)
