cmake_minimum_required(VERSION 3.10)

project(oarcle VERSION 1.1)

# Specify C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Look for all .cpp files
file(GLOB_RECURSE SOURCES "src/*.cpp")

include_directories(/usr/include/asio)

# Add files as proyect sources
add_executable(oarcle ${SOURCES})