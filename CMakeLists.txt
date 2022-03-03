# MIT License
# 
# Copyright (c) 2022 Erwan Saclier de la Bâtie
# 
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in all
# copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.

cmake_minimum_required(VERSION 3.16.0)
project(ini_parser 
    VERSION 0.1
    LANGUAGES CXX)

# enable c++11 standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Build the library static or shared.
option(BUILD_STATIC_LIBS "Build static lib" ON)
option(BUILD_SHARED_LIBS "Build shared lib" OFF)

include_directories(include/)

set(SOURCES 
    "src/ini_parser.cpp")

if (BUILD_STATIC_LIBS)
    add_library(ini_parser_static STATIC ${SOURCES})
    set_target_properties(ini_parser_static PROPERTIES ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
    install(TARGETS ini_parser_static DESTINATION lib)
endif()
if(BUILD_SHARED_LIBS)
    add_library(ini_parser SHARED ${SOURCES})
    if (WIN32)
        set_target_properties(ini_parser PROPERTIES LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
        install(TARGETS ini_parser
                ARCHIVE DESTINATION lib
                LIBRARY DESTINATION bin)
    else() 
        set_target_properties(ini_parser PROPERTIES LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
        install(TARGETS ini_parser
                ARCHIVE DESTINATION lib
                LIBRARY DESTINATION lib)
    endif()
    set_target_properties(ini_parser PROPERTIES ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
endif()

install (FILES ${CMAKE_SOURCE_DIR}/include/ini_parser.h
         DESTINATION include/ini_parser)