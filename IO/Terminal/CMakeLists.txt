cmake_minimum_required(VERSION 3.1.0)
#specify C params
set(CMAKE_C_COMPILER /usr/bin/clang-15)

# specify the C++ params
set(CMAKE_CXX_COMPILER /usr/bin/clang++-15)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# set the project name
project(Terminal VERSION 0.01)
include_directories(${PROJECT_SOURCE_DIR} /usr/include)

# CMake instructions to make the static lib

ADD_LIBRARY( SimpleANSITerminal STATIC src/ANSITerminal.cpp )
ADD_LIBRARY( SimpleWANSITerminal STATIC src/WANSITerminal.cpp )



SET( TERM_EXE TerminalTest )
SET( WTERM_EXE WTerminalTest )
# add the executable
add_executable( ${TERM_EXE}  src/main.cpp )
add_executable( ${WTERM_EXE} src/wmain.cpp )


TARGET_LINK_LIBRARIES( ${TERM_EXE}
                       SimpleANSITerminal )
TARGET_LINK_LIBRARIES( ${WTERM_EXE}
                       SimpleWANSITerminal )



