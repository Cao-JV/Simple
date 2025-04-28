# SimpleTerminal - A library for creating terminal-based systems (e.g. VT1.03)
# Provides basic character-based input & output routines
# Part of the Simple C++ Library
#
# Jagged\Verge
# Copyright (c) 2022-2025, Cao Smith

cmake_minimum_required(VERSION 3.16)

project(SimpleTerminal LANGUAGES CXX)

# Create the ANSI (standard) terminal static library
add_library(SimpleANSITerminal STATIC
    src/ANSITerminal.cpp
)

# Create the wide (UTF-16) terminal static library
add_library(SimpleWANSITerminal STATIC
    src/WANSITerminal.cpp
)

# Target settings for SimpleANSITerminal
target_include_directories(SimpleANSITerminal PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    $<INSTALL_INTERFACE:include>
)
target_compile_features(SimpleANSITerminal PUBLIC cxx_std_23)

# Target settings for SimpleWANSITerminal
target_include_directories(SimpleWANSITerminal PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    $<INSTALL_INTERFACE:include>
)
target_compile_features(SimpleWANSITerminal PUBLIC cxx_std_23)

# Create test executables
add_executable(TerminalTest
    src/main.cpp
)
target_link_libraries(TerminalTest PRIVATE SimpleANSITerminal)

add_executable(WTerminalTest
    src/wmain.cpp
)
target_link_libraries(WTerminalTest PRIVATE SimpleWANSITerminal)

# Install ANSI terminal library
install(TARGETS SimpleANSITerminal
    EXPORT SimpleTerminalTargets
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin
)

# Install wide terminal library
install(TARGETS SimpleWANSITerminal
    EXPORT SimpleTerminalTargets
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin
)

# Install headers
install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/
    DESTINATION include/SimpleTerminal
    FILES_MATCHING PATTERN "*.h"
)

# Export target config for find_package()
install(EXPORT SimpleTerminalTargets
    FILE SimpleTerminalTargets.cmake
    NAMESPACE SimpleTerminal::
    DESTINATION lib/cmake/SimpleTerminal
)
