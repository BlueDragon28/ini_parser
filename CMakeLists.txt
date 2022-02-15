cmake_minimum_required(VERSION 3.16.0)
project(ini_parser LANGUAGES CXX)

# enable c++11 standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Build the library static or shared.
option(BUILD_STATIC_LIBS ON)
option(BUILD_SHARED_LIBS OFF)

include_directories(include/)

set(SOURCES 
    "src/ini_parser.cpp")

if (BUILD_STATIC_LIBS)
    add_library(ini_parser STATIC ${SOURCES})
    set_target_properties(ini_parser PROPERTIES ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
endif()
if(BUILD_SHARED_LIBS)
    add_library(ini_parser SHARED ${SOURCES})
    if (WIN32)
        set_target_properties(ini_parser PROPERTIES LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
    else() 
        set_target_properties(ini_parser PROPERTIES LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
    endif()
    set_target_properties(ini_parser PROPERTIES ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
endif()