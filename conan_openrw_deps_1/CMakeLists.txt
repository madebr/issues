cmake_minimum_required(VERSION 3.2.2)

set(NAME conan_openrw_deps_1)

project("${NAME}")

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup(TARGETS)

add_executable(issue
    boost.cpp
    bullet.cpp
    ffmpeg.cpp
    openal.cpp
    sdl2.cpp
    main.cpp
    )

target_link_libraries(issue
    PUBLIC
        CONAN_PKG::boost_algorithm
        CONAN_PKG::boost_config
        CONAN_PKG::boost_filesystem
        CONAN_PKG::boost_program_options
        CONAN_PKG::boost_property_tree
        CONAN_PKG::bullet
        CONAN_PKG::ffmpeg
        CONAN_PKG::openal
        CONAN_PKG::sdl2
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
