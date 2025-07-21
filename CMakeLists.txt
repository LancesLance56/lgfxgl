cmake_minimum_required(VERSION 3.10)

set(CMAKE_C_COMPILER "C:/Program Files/w64devkit/bin/gcc.exe")
set(CMAKE_CXX_COMPILER "C:/Program Files/w64devkit/bin/g++.exe")

project(main)

# Set C++ standard to C++20
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_BUILD_TYPE Debug)

add_definitions(-DGLFW_INCLUDE_NONE)

# Set include directories
include_directories(
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_SOURCE_DIR}/src/gfx
        ${CMAKE_SOURCE_DIR}/include/imgui
        ${CMAKE_SOURCE_DIR}/include/imgui/backends
)

# Add source files
set(SOURCES
        include/glad.c
        include/imgui/imgui.cpp
        include/imgui/imgui.h
        include/imgui/imgui_demo.cpp
        include/imgui/imgui_draw.cpp
        include/imgui/imgui_tables.cpp
        include/imgui/imgui_widgets.cpp
        include/imgui/backends/imgui_impl_glfw.cpp
        include/imgui/backends/imgui_impl_glfw.h
        include/imgui/backends/imgui_impl_opengl3.cpp
        include/imgui/backends/imgui_impl_opengl3.h
    src/main.cpp
    src/gfx/window.cpp
    src/gfx/shader.cpp
    src/gfx/abo.cpp
    src/gfx/vao.cpp
    src/gfx/renderer.cpp
    src/gfx/texture.cpp
    src/gfx/camera.cpp
    src/handle_input.cpp
        src/math/perlin_noise_map.cpp
        src/math/perlin_noise_map.h
        src/math/perlin.cpp
        src/mesh/perlin_plane.h
        src/mesh/perlin_plane.cpp
        src/mesh/mesh.h
        src/mesh/mesh.cpp
        src/gfx/lightpos.h
        src/mesh/cube.cpp
        src/mesh/cube.h
        src/gfx/lightpos.cpp
        src/gfx/material.cpp
        src/gfx/material.h
        src/game.cpp
        src/game.h
        src/testgui.cpp
        src/testgui.h
        src/imgui/animation_curve.cpp
        src/imgui/animation_curve.h
        src/math/bezier.cpp
        src/math/bezier.h
        src/imgui/imgui_helper.cpp
        src/imgui/imgui_helper.h
        src/gfx/glad_include.h
)

# Add executable target
add_executable(main ${SOURCES})

# Link GLFW library
target_link_libraries(main ${CMAKE_SOURCE_DIR}/lib/libglfw3dll.a)
