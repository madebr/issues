cmake_minimum_required(VERSION 3.2.2)

set(NAME conan_test_all)

project("${NAME}")

#set(CONAN_LIBCXX "" FORCE)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

include("${CMAKE_BINARY_DIR}/conanbuildinfo.cmake")
conan_basic_setup()

find_package(Boost COMPONENTS program_options system REQUIRED)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(issue
    main.cpp
    )
target_link_libraries(issue
    PUBLIC
        Boost::program_options
        Boost::system
    )

enable_testing()

if(0)
    if(CONAN_SETTINGS_COMPILER_LIBCXX STREQUAL "libstdc++11")
        target_compile_definitions(issue PRIVATE _GLIBCXX_USE_CXX11_ABI=1)
    elseif(CONAN_SETTINGS_COMPILER_LIBCXX STREQUAL "libstdc++")
        target_compile_definitions(issue PRIVATE _GLIBCXX_USE_CXX11_ABI=1)
    endif()
endif()

add_test(
    NAME "${NAME}"
    COMMAND "$<TARGET_FILE:issue>"
    )

set_tests_properties("${NAME}"
    PROPERTIES
        TIMEOUT 10
    )
