project(test_package)
cmake_minimum_required(VERSION 3.1.0)

set(CMAKE_BUILD_TYPE "" CACHE STRING "BUILD_TYPE" FORCE)

if(EXISTS "${CMAKE_BINARY_DIR}/conanbuildinfo_multi.cmake")
    message(STATUS "Using conan 'cmake_multi' generator")
    include("${CMAKE_BINARY_DIR}/conanbuildinfo_multi.cmake")
    conan_basic_setup(TARGETS)
else()
    message(FATAL_ERROR "NO CONAN")
endif()

add_executable(${PROJECT_NAME}
    main.cpp
    )

target_link_libraries(${PROJECT_NAME}
    PRIVATE
        CONAN_PKG::Qt
        "$<IF:$<CONFIG:DEBUG>,${CONAN_LIB_DIRS_QT_DEBUG}/Qt5Widgetsd.lib,${CONAN_LIB_DIRS_QT_RELEASE}/Qt5Widgets.lib>"
        "$<IF:$<CONFIG:DEBUG>,${CONAN_LIB_DIRS_QT_DEBUG}/Qt5Cored.lib,${CONAN_LIB_DIRS_QT_RELEASE}/Qt5Core.lib>"
    )

message("${CONAN_INCLUDE_DIRS_QT_DEBUG}")
    
target_include_directories(${PROJECT_NAME}
    PRIVATE
        "$<IF:$<CONFIG:DEBUG>,${CONAN_INCLUDE_DIRS_QT_DEBUG}/QtWidgets,${CONAN_INCLUDE_DIRS_QT_RELEASE}/QtWidgets>"
    )
    