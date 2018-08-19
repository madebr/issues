project(test_package)
cmake_minimum_required(VERSION 3.1.0)

set(CMAKE_VERBOSE_MAKEFILE TRUE)

if(EXISTS "${CMAKE_BINARY_DIR}/conanbuildinfo_multi.cmake")
    message(STATUS "Using conan 'cmake_multi' generator")
    include("${CMAKE_BINARY_DIR}/conanbuildinfo_multi.cmake")
else()
    message(STATUS "Using conan 'cmake' generator")
    include("${CMAKE_BINARY_DIR}/conanbuildinfo.cmake")
endif()
conan_basic_setup(KEEP_RPATHS)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt5Core CONFIG REQUIRED)
find_package(Qt5Gui CONFIG REQUIRED)
find_package(Qt5OpenGL CONFIG REQUIRED)

add_executable(${PROJECT_NAME}
    main.cpp
    openglwindow.h
    openglwindow.cpp
    )

target_link_libraries(${PROJECT_NAME} Qt5::Core Qt5::OpenGL)
