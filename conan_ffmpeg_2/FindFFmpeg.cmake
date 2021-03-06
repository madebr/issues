# - Try to find ffmpeg libraries (libavcodec, libavformat and libavutil)
# Once done this will define
#
# FFMPEG_FOUND - system has ffmpeg or libav
# FFMPEG_INCLUDE_DIR - the ffmpeg include directory
# FFMPEG_LIBRARIES - Link these to use ffmpeg
# FFMPEG_LIBAVCODEC
# FFMPEG_LIBAVFORMAT
# FFMPEG_LIBAVUTIL
#
# Copyright (c) 2008 Andreas Schneider <mail@cynapses.org>
# Modified for other libraries by Lasse Kärkkäinen <tronic>
# Modified for Hedgewars by Stepik777
#
# Redistribution and use is allowed according to the terms of the New
# BSD license.
#

# use pkg-config to get the directories and then use these values
# in the FIND_PATH() and FIND_LIBRARY() calls
find_package(PkgConfig QUIET)
if (PKG_CONFIG_FOUND)
pkg_check_modules(_FFMPEG_AVCODEC libavcodec QUIET)
pkg_check_modules(_FFMPEG_AVFORMAT libavformat QUIET)
pkg_check_modules(_FFMPEG_AVUTIL libavutil QUIET)
endif (PKG_CONFIG_FOUND)

find_path(FFMPEG_AVCODEC_INCLUDE_DIR
NAMES libavcodec/avcodec.h
PATHS ${_FFMPEG_AVCODEC_INCLUDE_DIRS} /usr/include /usr/local/include /opt/local/include /sw/include
PATH_SUFFIXES ffmpeg libav
)

find_library(FFMPEG_LIBAVCODEC
NAMES avcodec libavcodec
PATHS ${_FFMPEG_AVCODEC_LIBRARY_DIRS} /usr/lib /usr/local/lib /opt/local/lib /sw/lib
PATH_SUFFIXES lib64 lib
)

find_library(FFMPEG_LIBAVFORMAT
NAMES avformat libavformat
PATHS ${_FFMPEG_AVFORMAT_LIBRARY_DIRS} /usr/lib /usr/local/lib /opt/local/lib /sw/lib
PATH_SUFFIXES lib64 lib
)

find_library(FFMPEG_LIBAVUTIL
NAMES avutil libavutil
PATHS ${_FFMPEG_AVUTIL_LIBRARY_DIRS} /usr/lib /usr/local/lib /opt/local/lib /sw/lib
PATH_SUFFIXES lib64 lib
)

find_library(FFMPEG_SWRESAMPLE
NAMES swresample libswresample
PATHS ${_FFMPEG_SWRESAMPLE_LIBRARY_DIRS} /usr/lib /usr/local/lib /opt/local/lib /sw/lib
PATH_SUFFIXES lib64 lib
)

set(FFMPEG_INCLUDE_DIR ${FFMPEG_AVCODEC_INCLUDE_DIR})

set(FFMPEG_LIBRARY_NAMES
FFMPEG_LIBAVCODEC
FFMPEG_LIBAVFORMAT
FFMPEG_LIBAVUTIL
)

if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
    list(APPEND FFMPEG_LIBRARY_NAMES "FFMPEG_SWRESAMPLE")
endif()

set(FFMPEG_LIBRARIES)
foreach(FFMPEG_LIB_NAME ${FFMPEG_LIBRARY_NAMES})
    list(APPEND FFMPEG_LIBRARIES "${${FFMPEG_LIB_NAME}}")
endforeach()

if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
    list(APPEND FFMPEG_LIBRARIES secur32.lib Ws2_32.lib)
endif()

message("FFMPEG_INCLUDE_DIR: ${FFMPEG_INCLUDE_DIR}")
message("FFMPEG_LIBAVCODEC:  ${FFMPEG_LIBAVCODEC}")
message("FFMPEG_LIBAVFORMAT: ${FFMPEG_LIBAVFORMAT}")
message("FFMPEG_LIBAVUTIL:   ${FFMPEG_LIBAVUTIL}")
message("FFMPEG_SWRESAMPLE:  ${FFMPEG_SWRESAMPLE}")

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(FFmpeg DEFAULT_MSG ${FFMPEG_LIBRARY_NAMES} FFMPEG_INCLUDE_DIR)
