project(test)
cmake_minimum_required(VERSION 3.0)

find_package(Qt5Widgets REQUIRED)
find_package(Qt5Test REQUIRED)

add_executable(window
    input_slider.hpp
    input_slider.cpp
    timetooltip.hpp
    timetooltip.cpp
    elements.hpp
    elements.cpp
    main_window.cpp
    )

set_property(TARGET window
    PROPERTY
        AUTOMOC ON
    )

target_link_libraries(window
    PUBLIC
        Qt5::Widgets
    )