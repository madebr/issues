cmake_minimum_required(VERSION 3.2.2)

set(NAME conan_ffmpeg_issue_2)

project("${NAME}")

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}")

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

message("CMAKE_INCLUDE_PATH: ${CMAKE_INCLUDE_PATH}")
message("CMAKE_LIBRARY_PATH: ${CMAKE_LIBRARY_PATH}")

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

set_tests_properties("${NAME}"
    PROPERTIES
        TIMEOUT 10
    )
