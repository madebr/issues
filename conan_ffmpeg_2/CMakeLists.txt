cmake_minimum_required(VERSION 3.2.2)

set(NAME conan_ffmpeg_issue_1)

project("${NAME}")

list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}")

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup(TARGETS)

find_package(FFmpeg REQUIRED)

add_executable(issue main.cpp)
target_link_libraries(issue
    PUBLIC
        "${FFMPEG_LIBRARIES}"
    )
target_include_directories(issue
    PUBLIC
        "${FFMPEG_INCLUDE_DIR}"
    )

enable_testing()

add_test(
    NAME "${NAME}"
    COMMAND "$<TARGET_FILE:issue>"
    )