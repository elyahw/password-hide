cmake_minimum_required(VERSION 3.0)

project(keygen LANGUAGES CXX)

add_executable(key_gen key_gen.cpp)

target_link_libraries(key_gen)
