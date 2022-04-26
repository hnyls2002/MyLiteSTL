cmake_minimum_required(VERSION 3.16)
project(linked_hashmap)

set(CMAKE_CXX_STANDARD 14)

add_executable(linked_hashmap main.cpp exceptions.hpp linked_hashmap.hpp utility.hpp)
