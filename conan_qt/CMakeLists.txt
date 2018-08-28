project(test_package)
cmake_minimum_required(VERSION 3.1.0)

set(CMAKE_BUILD_TYPE "" CACHE STRING "BUILD_TYPE" FORCE)

if(EXISTS "${CMAKE_BINARY_DIR}/conanbuildinfo_multi.cmake")
    message(STATUS "Using conan 'cmake_multi' generator")
    include("${CMAKE_BINARY_DIR}/conanbuildinfo_multi.cmake")
    conan_basic_setup()
else()
    message(FATAL_ERROR "NO CONAN")
endif()

message("CMAKE_MODULE_PATH before fix: ${CMAKE_MODULE_PATH}")

set(CMAKE_PREFIX_PATH
    ${CONAN_CMAKE_MODULE_PATH_DEBUG} ${CONAN_CMAKE_MODULE_PATH_RELEASE} ${CMAKE_PREFIX_PATH}
    )
set(CMAKE_MODULE_PATH
    ${CONAN_CMAKE_MODULE_PATH_DEBUG} ${CONAN_CMAKE_MODULE_PATH_RELEASE} ${CMAKE_MODULE_PATH}
    )

message("CMAKE_MODULE_PATH after fix: ${CMAKE_MODULE_PATH}")
        

find_package(Qt5Widgets REQUIRED)
get_target_property(QT5_W_IC Qt5::Widgets IMPORTED_CONFIGURATIONS)

message("Qt5::Widgets IMPORTED_CONFIGURATIONS: ${QT5_W_IC}")

add_executable(${PROJECT_NAME}
    main.cpp
    )

target_link_libraries(${PROJECT_NAME}
    Qt5::Widgets
    )
