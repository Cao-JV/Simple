# Simple Library: An unsophisticated set of straight-forward classes, providing vanilla solutions to common needs
# Simple Logger: A class to write things to a file

cmake_minimum_required(VERSION 3.10)
#specify C params
set(CMAKE_C_COMPILER /usr/bin/clang-12)

# specify the C++ params
set(CMAKE_CXX_COMPILER /usr/bin/clang++-12)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# set the project name
project(SimpleLogging VERSION 0.01)
include_directories(${PROJECT_SOURCE_DIR} /usr/include)

# CMake instructions to make the static lib
ADD_LIBRARY( SimpleLogger STATIC src/ALogger.cpp src/Logger.cpp )
ADD_LIBRARY( SimpleWLogger STATIC src/ALogger.cpp src/WLogger.cpp )



SET( LOG_EXE LogTest )
SET( WLOG_EXE WLogTest )
# add the executable
add_executable( ${LOG_EXE}  src/main.cpp )
add_executable( ${WLOG_EXE} src/wmain.cpp )


TARGET_LINK_LIBRARIES( ${LOG_EXE}
                       SimpleLogger )
 TARGET_LINK_LIBRARIES( ${WLOG_EXE}
                     SimpleWLogger )
