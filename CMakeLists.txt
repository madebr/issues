cmake_minimum_required(VERSION 3.16)
project(sdl_test)

find_package(SDL3 REQUIRED)

add_executable(main main.c)
target_link_libraries(main PRIVATE SDL3::SDL3)

