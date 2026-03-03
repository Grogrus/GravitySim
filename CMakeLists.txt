cmake_minimum_required(VERSION 3.16)
project(GravitySim)

set(CMAKE_CXX_STANDARD 17)

# ─── Abhängigkeiten automatisch herunterladen ────────────────────────────────
include(FetchContent)

# GLFW
FetchContent_Declare(
    glfw
    GIT_REPOSITORY https://github.com/glfw/glfw.git
    GIT_TAG        3.4
)
set(GLFW_BUILD_DOCS     OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS    OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(glfw)

# glad2 (keine Python-Abhängigkeit, keine Netzwerkverbindung beim Build nötig)
FetchContent_Declare(
    glad
    GIT_REPOSITORY https://github.com/Dav1dde/glad.git
    GIT_TAG        glad2
    SOURCE_SUBDIR  cmake
)
FetchContent_MakeAvailable(glad)

glad_add_library(glad_gl_core REPRODUCIBLE API gl:core=3.3)

# ─── Executable ──────────────────────────────────────────────────────────────
add_executable(GravitySim
    src/main.cpp
    src/simulation.cpp
    src/object.cpp
    src/physics.cpp
    src/database.cpp
    src/ui.cpp
    src/imgui/imgui.cpp
    src/imgui/imgui_draw.cpp
    src/imgui/imgui_tables.cpp
    src/imgui/imgui_widgets.cpp
    src/imgui/imgui_impl_glfw.cpp
    src/imgui/imgui_impl_opengl3.cpp
)

# ─── Include-Verzeichnisse ───────────────────────────────────────────────────
target_include_directories(GravitySim PRIVATE
    include        # glm, imgui headers, eigene headers
    include/imgui
)

# ─── Linker ──────────────────────────────────────────────────────────────────
target_link_libraries(GravitySim PRIVATE
    glfw           # GLFW (compiler-unabhängig)
    glad_gl_core   # glad2
    opengl32       # Windows OpenGL
    gdi32          # Windows GDI
)