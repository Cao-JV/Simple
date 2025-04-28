# SimpleLibrary - A Convenience Collection of Simple C++ Libraries
# Combines libraries such as SimpleSocket, SimpleTerminal, and others
# Part of the Simple C++ Library
#
# Jagged\Verge
# Copyright (c) 2019-2025, Cao Smith

cmake_minimum_required(VERSION 3.16)

project(SimpleLibrary LANGUAGES CXX)

# Add subprojects
add_subdirectory(SimpleSocket)
add_subdirectory(SimpleTerminal)

# Optionally create a meta-library to link everything together
add_library(SimpleLibrary INTERFACE)

# Link all sublibraries into SimpleLibrary
target_link_libraries(SimpleLibrary
    INTERFACE
    SimpleSocket
    SimpleTerminal
)

# Install headerless interface library (optional)
install(TARGETS SimpleLibrary
    EXPORT SimpleLibraryTargets
)

# Export each sublibrary's install targets
install(EXPORT SimpleLibraryTargets
    FILE SimpleLibraryTargets.cmake
    NAMESPACE SimpleLibrary::
    DESTINATION lib/cmake/SimpleLibrary
)
