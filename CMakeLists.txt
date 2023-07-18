cmake_minimum_required(VERSION 3.22)
project(issues C)

enable_testing()

#find_package(SDL2 CONFIG REQUIRED)
find_package(SDL3 CONFIG REQUIRED)
function(add_sdl_test_executable TARGET)
    cmake_parse_arguments(ARGS "" "" "SOURCES" ${ARGN})

#    add_executable(sdl2_${TARGET} ${ARGS_SOURCES})
#    target_link_libraries(sdl2_${TARGET} PRIVATE SDL2::SDL2)
#    target_compile_definitions(sdl2_${TARGET} PRIVATE WITH_SDL2)
#    add_test(sdl2_${TARGET} sdl2_${TARGET})
#    set_tests_properties(sdl2_${TARGET} PROPERTIES TIMEOUT 20)

    add_executable(sdl3_${TARGET} ${ARGS_SOURCES})
    target_link_libraries(sdl3_${TARGET} PRIVATE SDL3::SDL3_test SDL3::SDL3)
    target_compile_definitions(sdl3_${TARGET} PRIVATE WITH_SDL3)
    add_test(sdl3_${TARGET} sdl3_${TARGET})
    get_property(SDL3_DLL TARGET SDL3::SDL3-shared PROPERTY IMPORTED_LOCATION_RELEASE)
    get_filename_component(SDL3_DIR "${SDL3_DLL}" DIRECTORY)
    set_tests_properties(sdl3_${TARGET} PROPERTIES
        TIMEOUT 20
        ENVIRONMENT "SDL_AUDIODRIVER=dummy;SDL_VIDEODRIVER=dummy;SDL_AUDIO_DRIVER=dummy;SDL_VIDEO_DRIVER=dummy;SDL_TESTS_QUICK=1;PATH=${SDL3_DIR}"
    )
#    add_custom_command(TARGET sdl3_${TARGET} POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_RUNTIME_DLLS:sdl3_${TARGET}> $<TARGET_FILE_DIR:sdl3_${TARGET}> COMMAND_EXPAND_LISTS)
endfunction()

add_sdl_test_executable(testsurround SOURCES testsurround.c)
add_sdl_test_executable(testaudioinfo SOURCES testaudioinfo.c)
add_sdl_test_executable(testatomic SOURCES testatomic.c)
add_sdl_test_executable(testerror SOURCES testerror.c)
add_sdl_test_executable(testevdev SOURCES testevdev.c)
add_sdl_test_executable(testfile SOURCES testfile.c)
add_sdl_test_executable(testthread SOURCES testthread.c)
add_sdl_test_executable(testkeys SOURCES testthread.c)
add_sdl_test_executable(testlocale SOURCES testlocale.c)


#add_executable(main_sdl3 main.c)
#target_link_libraries(main_sdl3 PRIVATE SDL3::SDL3-shared)
#target_compile_definitions(main_sdl3 PRIVATE WITH_SDL3)
#add_custom_command(TARGET main_sdl3 POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:SDL3::SDL3-shared> $<TARGET_FILE_DIR:main_sdl3>)
#
#add_executable(testthread_sdl3 testthread.c)
#target_link_libraries(testthread_sdl3 PRIVATE SDL3::SDL3-shared)
#target_compile_definitions(testthread_sdl3 PRIVATE WITH_SDL3)
#
#add_executable(main_sdl2 main.c)
#target_link_libraries(main_sdl2 PRIVATE SDL2::SDL2)
#target_compile_definitions(main_sdl2 PRIVATE WITH_SDL2)
#add_custom_command(TARGET main_sdl3 POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:SDL2::SDL2> $<TARGET_FILE_DIR:main_sdl2>)
#
#add_executable(testthread_sdl2 testthread.c)
#target_link_libraries(testthread_sdl2 PRIVATE SDL2::SDL2)
#target_compile_definitions(testthread_sdl2 PRIVATE WITH_SDL2)
#
#enable_testing()
#set(i 0)
#while(i LESS 100)
#    add_test(sdl2_test_${i} main_sdl2)
#    add_test(sdl2_thread_${i} testthread_sdl2)
#
#    add_test(sdl3_test_${i} main_sdl3)
#    add_test(sdl3_thread_${i} testthread_sdl3)
#
#    set_tests_properties(
#            sdl2_test_${i} sdl2_thread_${i}
#            sdl3_test_${i} sdl3_thread_${i}
#        PROPERTIES TIMEOUT 10
#        ENVIRONMENT "SDL_AUDIODRIVER=dummy;SDL_VIDEODRIVER=dummy;SDL_AUDIO_DRIVER=dummy;SDL_VIDEO_DRIVER=dummy;SDL_TESTS_QUICK=1"
#    )
#
#    math(EXPR i "${i}+1")
#endwhile()
