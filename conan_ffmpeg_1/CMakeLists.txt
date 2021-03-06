cmake_minimum_required(VERSION 3.2.2)

set(NAME conan_ffmpeg_issue_1)

project("${NAME}")

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup(TARGETS)

add_executable(issue main.cpp)
target_link_libraries(issue
    PUBLIC
        CONAN_PKG::ffmpeg
    )

if(MSVC)
    target_compile_options(issue
	PUBLIC
	    "/wd4099"
	)
endif()

enable_testing()

add_test(
    NAME "${NAME}"
    COMMAND "$<TARGET_FILE:issue>"
    )

set_tests_properties("${NAME}"
    PROPERTIES
        TIMEOUT 10
    )
