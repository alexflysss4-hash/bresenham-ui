cmake_minimum_required(VERSION 3.16)
project(BresenhamUI)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Rutas
set(IMGUI_DIR "${CMAKE_CURRENT_SOURCE_DIR}/imgui")

# Archivos de Dear ImGui
set(IMGUI_SOURCES
    ${IMGUI_DIR}/imgui.cpp
    ${IMGUI_DIR}/imgui_demo.cpp
    ${IMGUI_DIR}/imgui_draw.cpp
    ${IMGUI_DIR}/imgui_tables.cpp
    ${IMGUI_DIR}/imgui_widgets.cpp
    ${IMGUI_DIR}/backends/imgui_impl_sdl2.cpp
    ${IMGUI_DIR}/backends/imgui_impl_opengl3.cpp
)

# Crear ejecutable
add_executable(BresenhamUI
    src/main.cpp
    src/bresenham.cpp
    ${IMGUI_SOURCES}
)

# Incluir directorios
target_include_directories(BresenhamUI PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${IMGUI_DIR}
    ${IMGUI_DIR}/backends
)

# Encontrar SDL2 y OpenGL
find_package(SDL2 REQUIRED)
find_package(OpenGL REQUIRED)

# Vincular librerías
target_link_libraries(BresenhamUI
    SDL2::SDL2
    OpenGL::OpenGL
)

# Establecer como proyecto de inicio en Visual Studio
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT BresenhamUI)
