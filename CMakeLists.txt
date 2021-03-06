cmake_minimum_required(VERSION 3.10.2)
project(myshell CXX)

set(CMAKE_CXX_STANDARD 17)

# Options
option(WARNINGS_AS_ERRORS   "Treat compiler warnings as errors."    OFF)
option(ENABLE_SANITIZERS    "Use sanitizers to detect errors."      OFF)
option(ENABLE_CONAN         "Use Conan as a package manager."       OFF)

# Include fixed CMake configuration
include(cmake/config.cmake)

# Project source compilation
include_directories(inc)

# For semaphore
find_package(Threads)

# parse h
add_library(parse SHARED src/parse/parse.cpp inc/parse/parse.hpp)

# internal programs
add_library(internal SHARED
        src/internal/pwd/mpwd.cpp
                src/internal/main.cpp
        src/internal/exit/mexit.cpp
        src/internal/echo/mecho.cpp
        src/internal/cd/mcd.cpp
        src/internal/export/mexport.cpp
        src/internal/errno/merrno.cpp
        src/internal/dot/mdot.cpp
        src/internal/add_local_var.cpp
            inc/internal/internal.hpp)

# util
add_library(util SHARED src/util/dir.cpp
                        src/util/infinity_loop.cpp
                        src/util/run_program.cpp
                        src/util/env.cpp
                        src/util/util.cpp
                        src/server/main.cpp
        inc/util/util.h)

# consts
add_library(errors SHARED src/util/errors/errors.cpp inc/util/errors.h)

#
add_library(IO SHARED src/util/IO.cpp inc/IO/IO.h)

target_link_libraries(util parse internal errors IO)


add_executable(myshell src/main.cpp)

target_link_libraries(myshell parse util ${CMAKE_THREAD_LIBS_INIT})

# Add external packages
#find_package(Boost 1.65.1 COMPONENTS regex REQUIRED)
#include_directories(${Boost_INCLUDE_DIR})

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH}
        ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

# Actually search for the library
find_package(Readline)

# Use the headers directory
include_directories(${Readline_INCLUDE_DIR})
# Link a target that uses the library
target_link_libraries(myshell  ${Readline_LIBRARY})

# Sanitizers configuration
if (ENABLE_SANITIZERS)
    set(SANITIZE_UNDEFINED ON)
    # Only one of Memory, Address, or Thread sanitizers is applicable at the time
    set(SANITIZE_MEMORY ON)
#    set(SANITIZE_ADDRESS ON)
#    set(SANITIZE_THREAD ON)
    find_package(Sanitizers)

    # CMake targets to which apply sanitizers
    add_sanitizers(operations myshell)
endif ()