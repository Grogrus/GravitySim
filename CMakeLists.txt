cmake_minimum_required(VERSION 3.10)
project(GravitySim)

set(CMAKE_CXX_STANDARD 17)

# Include-Verzeichnisse (glad, glfw, eigene headers)
include_directories(include)

add_executable(GravitySim
    src/main.cpp
    src/simulation.cpp
    src/object.cpp
    src/physics.cpp
    src/database.cpp
    src/ui.cpp
    src/glad.c
)

# Linker: GLFW (statisch), OpenGL und GDI (Windows)
target_link_libraries(GravitySim
    ${CMAKE_SOURCE_DIR}/libs/libglfw3.a
    opengl32
    gdi32
)

# glfw3.dll automatisch neben die .exe kopieren
add_custom_command(TARGET GravitySim POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${CMAKE_SOURCE_DIR}/libs/glfw3.dll"
        $<TARGET_FILE_DIR:GravitySim>
)