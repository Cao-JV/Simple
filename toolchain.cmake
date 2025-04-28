# SimpleLibraryToolchain.cmake
# Toolchain file for SimpleLibrary projects
# Default compilers and settings for POSIX and NT systems
# Copyright (c) 2019-2025, Cao Smith
# Jagged\Verge

# Only set compilers if not already defined
if(NOT DEFINED CMAKE_C_COMPILER)
    set(CMAKE_C_COMPILER /usr/bin/clang-19)
endif()

if(NOT DEFINED CMAKE_CXX_COMPILER)
    set(CMAKE_CXX_COMPILER /usr/bin/clang++-19)
endif()

# Optionally specify system processor or sysroot if cross-compiling
# set(CMAKE_SYSTEM_PROCESSOR x86_64)
# set(CMAKE_SYSROOT /opt/mysysroot)