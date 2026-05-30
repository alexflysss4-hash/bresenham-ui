# Bresenham Algorithms UI - C++ con Dear ImGui

Una aplicación interactiva para visualizar y trabajar con los **Algoritmos de Bresenham** (líneas y círculos) usando Dear ImGui como interfaz gráfica.

## Características

✨ **Algoritmos Implementados:**
- ✅ Línea de Bresenham
- ✅ Círculo de Bresenham  
- ✅ Círculo relleno

🎨 **Interfaz Gráfica:**
- Panel de control con Dear ImGui
- Selector de color RGB
- Canvas de dibujo interactivo (800x600)
- Historial de figuras dibujadas
- Botón para limpiar canvas

🖱️ **Interacción:**
- Selecciona el modo de dibujo (línea, círculo, círculo relleno)
- Elige el color con el color picker
- Haz clic y arrastra en el canvas para dibujar
- Visualiza en tiempo real

## Requisitos Previos

### Para Windows (Visual Studio 2019+):

1. **CMake** (3.16+)
   - Descarga desde: https://cmake.org/download/

2. **Visual Studio 2019 o superior**
   - Con soporte C++17

3. **vcpkg** (Gestor de paquetes para Visual Studio)
   ```bash
   git clone https://github.com/Microsoft/vcpkg.git
   cd vcpkg
   .\bootstrap-vcpkg.bat
   ```

## Instalación de Dependencias

### Usando vcpkg:

```bash
# Instalar SDL2
vcpkg install sdl2:x64-windows

# Instalar OpenGL (si es necesario)
vcpkg install opengl:x64-windows
```

### O instalar manualmente:
- **SDL2**: https://www.libsdl.org/download-2.0.php
- **Dear ImGui**: Incluido en el proyecto

## Compilación y Ejecución

### Opción 1: Usando CMake GUI (Recomendado para Visual Studio)

```bash
# Crear carpeta de build
mkdir build
cd build

# Generar solución Visual Studio
cmake .. -G "Visual Studio 16 2019" -DCMAKE_TOOLCHAIN_FILE=C:\path\to\vcpkg\scripts\buildsystems\vcpkg.cmake

# Abrir la solución generada
# Luego compilar y ejecutar desde Visual Studio
```

### Opción 2: Línea de comandos

```bash
mkdir build
cd build
cmake .. -G "Visual Studio 16 2019" -DCMAKE_TOOLCHAIN_FILE="C:\vcpkg\scripts\buildsystems\vcpkg.cmake"
cmake --build . --config Release
```

### Ejecutar:
```bash
.\Release\BresenhamUI.exe
```

## Estructura del Proyecto

```
bresenham-ui/
├── include/
│   └── bresenham.h           # Definiciones de algoritmos
├── src/
│   ├── main.cpp              # Aplicación principal con ImGui
│   └── bresenham.cpp         # Implementación de algoritmos
├── imgui/                    # Dear ImGui (submodulo)
│   ├── backends/
│   ├── imgui.h
│   └── ...
├── CMakeLists.txt            # Configuración de compilación
└── README.md                 # Este archivo
```

## Cómo Usar

1. **Selecciona el modo de dibujo:**
   - Línea Bresenham
   - Círculo Bresenham
   - Círculo Relleno

2. **Elige el color:**
   - Usa el color picker en el panel de control

3. **Dibuja en el canvas:**
   - Haz clic y arrastra para crear figuras
   - Para líneas: del punto inicial al final
   - Para círculos: centro y punto en el perímetro

4. **Gestiona el canvas:**
   - El historial muestra todas las figuras dibujadas
   - Botón "Limpiar Canvas" para empezar de nuevo

## Algoritmos Implementados

### Línea de Bresenham
```cpp
std::vector<Point> drawLine(int x0, int y0, int x1, int y1);
```
Dibuja una línea entre dos puntos usando el algoritmo incremental de Bresenham.

### Círculo de Bresenham
```cpp
std::vector<Point> drawCircle(int xc, int yc, int radius);
```
Dibuja el perímetro de un círculo usando el algoritmo de punto medio.

### Círculo Relleno
```cpp
std::vector<Point> fillCircle(int xc, int yc, int radius);
```
Rellena un círculo dibujando círculos concéntricos.

## Solución de Problemas

### "SDL2 not found"
- Asegúrate de tener SDL2 instalado vía vcpkg
- Verifica la ruta del toolchain en CMake

### "imgui.h not found"
- Clona Dear ImGui en la carpeta `imgui/`
- ```bash
  git clone https://github.com/ocornut/imgui.git imgui
  ```

### Errores de compilación de OpenGL
- En Windows, OpenGL usualmente viene con el driver de gráficos
- Si persiste el error, instala: `vcpkg install opengl:x64-windows`

## Dependencias Principales

- **SDL2**: Ventanas y manejo de eventos
- **OpenGL 3.2+**: Renderizado gráfico
- **Dear ImGui**: Interfaz gráfica
- **C++17**: Características del lenguaje

## Autores

Proyecto desarrollado para demostrar los Algoritmos de Bresenham en una interfaz moderna.

## Licencia

Este proyecto utiliza Dear ImGui bajo licencia MIT.

---

¡Disfruta dibujando con Bresenham! 🎨
