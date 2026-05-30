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

# Para Windows - Usar SDL2 y OpenGL del sistema
if(WIN32)
    # Buscar SDL2
    find_package(SDL2 CONFIG QUIET)
    if(NOT SDL2_FOUND)
        # Si no está en el path de CMake, intentar buscar manualmente
        find_package(SDL2 QUIET)
    endif()
    
    # Buscar OpenGL
    find_package(OpenGL REQUIRED)
    
    if(SDL2_FOUND)
        target_link_libraries(BresenhamUI PRIVATE SDL2::SDL2 OpenGL::OpenGL)
    else()
        message(FATAL_ERROR "SDL2 no encontrado. Ejecuta en PowerShell: vcpkg install sdl2:x64-windows")
    endif()
else()
    # Para Linux/Mac
    find_package(SDL2 REQUIRED)
    find_package(OpenGL REQUIRED)
    target_link_libraries(BresenhamUI PRIVATE SDL2::SDL2 OpenGL::OpenGL)
endif()

# Establecer como proyecto de inicio en Visual Studio
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT BresenhamUI)

message(STATUS "✓ Configuración completada")
message(STATUS "  - ImGui: ${IMGUI_DIR}")
message(STATUS "  - Generador: ${CMAKE_GENERATOR}")
