cmake_minimum_required(VERSION 3.2.2)

set(NAME conan_bullet_issue_1)

project("${NAME}")

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

find_package(Boost COMPONENTS REQUIRED)

add_executable(issue main.cpp)
target_include_directories(issue
    PUBLIC
        ${Boost_INCLUDE_DIRS}
    )

enable_testing()

add_test(
    NAME "${NAME}"
    COMMAND "$<TARGET_FILE:issue>"
    )
