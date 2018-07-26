project(test)
cmake_minimum_required(VERSION 3.0)

find_package(Qt5Widgets REQUIRED)

add_executable(window
    main.cpp
    )

target_link_libraries(window
    PUBLIC
        Qt5::Widgets
    )