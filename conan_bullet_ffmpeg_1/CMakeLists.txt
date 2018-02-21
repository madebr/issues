cmake_minimum_required(VERSION 3.2.2)

set(NAME conan_boost)

project("${NAME}")

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup(TARGETS)

add_executable(issue main.cpp)
target_link_libraries(issue
    PUBLIC
        CONAN_PKG::ffmpeg
        CONAN_PKG::bullet
    )

enable_testing()

add_test(
    NAME "${NAME}"
    COMMAND "$<TARGET_FILE:issue>"
    )