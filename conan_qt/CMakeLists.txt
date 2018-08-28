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
    ${CONAN_CMAKE_MODULE_PATH_RELEASE} ${CONAN_CMAKE_MODULE_PATH_DEBUG} ${CMAKE_PREFIX_PATH}
    )
set(CMAKE_MODULE_PATH
    ${CONAN_CMAKE_MODULE_PATH_RELEASE} ${CONAN_CMAKE_MODULE_PATH_DEBUG} ${CMAKE_MODULE_PATH}
    )

message("CMAKE_MODULE_PATH after fix: ${CMAKE_MODULE_PATH}")
        
find_package(Qt5Widgets REQUIRED)

get_target_property(QT5_W_IC Qt5::Widgets IMPORTED_CONFIGURATIONS)
message("Qt5::Widgets IMPORTED_CONFIGURATIONS: ${QT5_W_IC}")

get_target_property(QT5_W_LI Qt5::Widgets INTERFACE_LINK_LIBRARIES)
message("Qt5::Widgets INTERFACE_LINK_LIBRARIES: ${QT5_W_LI}")

get_target_property(QT5_W_IL Qt5::Widgets IMPORTED_LOCATION)
get_target_property(QT5_W_IL_R Qt5::Widgets IMPORTED_LOCATION_RELEASE)
get_target_property(QT5_W_IL_D Qt5::Widgets IMPORTED_LOCATION_REBUG)
message("Qt5::Widgets IMPORTED_LOCATION: ${QT5_W_IL}")
message("Qt5::Widgets IMPORTED_LOCATION_RELEASE: ${QT5_W_IL_R}")
message("Qt5::Widgets IMPORTED_LOCATION_DEBUG: ${QT5_W_IL_D}")

get_target_property(QT5_W_ILIL Qt5::Widgets IMPORTED_LINK_INTERFACE_LIBRARIES)
get_target_property(QT5_W_ILIL_R Qt5::Widgets IMPORTED_LINK_INTERFACE_LIBRARIES_RELEASE)
get_target_property(QT5_W_ILIL_D Qt5::Widgets IMPORTED_LINK_INTERFACE_LIBRARIES_DEBUG)
message("Qt5::Widgets IMPORTED_LINK_INTERFACE_LIBRARIES: ${QT5_W_ILIL}")
message("Qt5::Widgets IMPORTED_LINK_INTERFACE_LIBRARIES_RELEASE: ${QT5_W_ILIL_R}")
message("Qt5::Widgets IMPORTED_LINK_INTERFACE_LIBRARIES_DEBUG: ${QT5_W_ILIL_D}")

get_target_property(QT5_W_II Qt5::Widgets IMPORTED_IMPLIB)
get_target_property(QT5_W_II_R Qt5::Widgets IMPORTED_IMPLIB_RELEASE)
get_target_property(QT5_W_II_D Qt5::Widgets IMPORTED_IMPLIB_DEBUG)
message("Qt5::Widgets IMPORTED_IMPLIB: ${QT5_W_II}")
message("Qt5::Widgets IMPORTED_IMPLIB_RELEASE: ${QT5_W_II_R}")
message("Qt5::Widgets IMPORTED_IMPLIB_DEBUG: ${QT5_W_II_D}")

add_executable(${PROJECT_NAME}
    main.cpp
    )

target_link_libraries(${PROJECT_NAME}
    Qt5::Widgets
    )
