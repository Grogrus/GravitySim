cmake_minimum_required(VERSION 3.16)
project(GravitySim)

set(CMAKE_CXX_STANDARD 17)

# GLFW automatisch herunterladen und bauen
include(FetchContent)
FetchContent_Declare(
    glfw
    GIT_REPOSITORY https://github.com/glfw/glfw.git
    GIT_TAG        3.4
)
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(glfw)

include_directories(include)
include_directories(include/imgui)

add_executable(GravitySim
    src/main.cpp
    src/simulation.cpp
    src/object.cpp
    src/physics.cpp
    src/database.cpp
    src/ui.cpp
    src/glad.c
    src/imgui/imgui.cpp
    src/imgui/imgui_draw.cpp
    src/imgui/imgui_tables.cpp
    src/imgui/imgui_widgets.cpp
    src/imgui/imgui_impl_glfw.cpp
    src/imgui/imgui_impl_opengl3.cpp
)

target_link_libraries(GravitySim
    glfw           
    opengl32
    gdi32
)