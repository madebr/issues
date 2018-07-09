cmake_minimum_required(VERSION 3.2.2)

set(NAME conan_boost_test_1)

project("${NAME}")

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

find_package(Boost COMPONENTS unit_test_framework REQUIRED)

add_executable(issue
    main.cpp
    test_nop.cpp
)

target_link_libraries(issue
    PUBLIC
        Boost::unit_test_framework
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
