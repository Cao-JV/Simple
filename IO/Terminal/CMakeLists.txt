cmake_minimum_required(VERSION 3.10)
#specify C params
set(CMAKE_C_COMPILER /usr/bin/clang-12)

# specify the C++ params
set(CMAKE_CXX_COMPILER /usr/bin/clang++-12)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# set the project name
project(Terminal)

# add the executable
include_directories(${PROJECT_SOURCE_DIR} /usr/include)
add_executable(WTerminal src/WANSITerminal.cpp src/wmain.cpp)
add_executable(Terminal src/ANSITerminal.cpp src/main.cpp)

