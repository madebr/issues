cmake_minimum_required(VERSION 3.2.2)

set(NAME conan_boost)

project("${NAME}")

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

find_package(Boost COMPONENTS program_options system REQUIRED)

add_executable(issue main.cpp
    boost.cpp
    )
target_link_libraries(issue
    PRIVATE
        Boost::program_options
        Boost::system
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
