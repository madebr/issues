cmake_minimum_required(VERSION 3.20)
project(sdl_test C)

find_package(SDL2 CONFIG REQUIRED)
find_package(SDL3 CONFIG REQUIRED)

add_executable(main_sdl3 main.c)
target_link_libraries(main_sdl3 PRIVATE SDL3::SDL3-shared)
target_compile_definitions(main_sdl3 PRIVATE WITH_SDL3)
add_custom_command(TARGET main_sdl3 POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:SDL3::SDL3-shared> $<TARGET_FILE_DIR:main_sdl3>)

add_executable(main_sdl2 main.c)
target_link_libraries(main_sdl2 PRIVATE SDL2::SDL2)
target_compile_definitions(main_sdl2 PRIVATE WITH_SDL2)
add_custom_command(TARGET main_sdl3 POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:SDL2::SDL2> $<TARGET_FILE_DIR:main_sdl2>)
