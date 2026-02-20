cmake_minimum_required(VERSION 3.10)
project(GravitySim)

set(CMAKE_CXX_STANDARD 17)

# Hier sagst du dem Compiler: schau auch in /include rein
include_directories(include)

add_executable(GravitySim
    src/main.cpp
    src/simulation.cpp
    src/object.cpp
    src/physics.cpp
    src/database.cpp
    src/ui.cpp
)