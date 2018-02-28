cmake_minimum_required(VERSION 3.2.2)

set(NAME conan_boost_algorithm_1)

project("${NAME}")

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

find_package(Boost REQUIRED)

add_executable(issue main.cpp)
target_include_directories(issue
    PUBLIC
        ${Boost_INCLUDE_DIRS}
    )

message("Boost_INCLUDE_DIRS=${Boost_INCLUDE_DIRS}")

enable_testing()

add_test(
    NAME "${NAME}"
    COMMAND "$<TARGET_FILE:issue>"
    )

set_tests_properties("${NAME}"
    PROPERTIES
        TIMEOUT 10
    )
