project(test_package)
cmake_minimum_required(VERSION 3.1.0)

set(CMAKE_VERBOSE_MAKEFILE TRUE)

if(EXISTS "${CMAKE_BINARY_DIR}/conanbuildinfo_multi.cmake")
    message(STATUS "Using conan 'cmake_multi' generator")
    include("${CMAKE_BINARY_DIR}/conanbuildinfo_multi.cmake")
    conan_basic_setup(TARGETS)
elseif(EXISTS "${CMAKE_BINARY_DIR}/conanbuildinfo.cmake")
    message(STATUS "Using conan 'cmake' generator")
    include("${CMAKE_BINARY_DIR}/conanbuildinfo.cmake")
    conan_basic_setup(TARGETS)
else()
    message(STATUS "NO CONAN")
endif()

find_package(Qt5Widgets REQUIRED)

add_executable(${PROJECT_NAME} WIN32
    main.cpp
    )

target_link_libraries(${PROJECT_NAME}
    Qt5::WinMain
    Qt5::Widgets
    )
