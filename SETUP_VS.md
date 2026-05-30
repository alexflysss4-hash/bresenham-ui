# Guía de Setup para Visual Studio 2019/2022

## Paso 1: Instalar Herramientas Necesarias

### 1.1 Descargar e instalar CMake
- Descarga desde: https://cmake.org/download/
- Versión recomendada: 3.22+
- Durante la instalación, marca la opción **"Add CMake to the system PATH"**

### 1.2 Descargar e instalar Visual Studio
- Si no tienes Visual Studio 2019+, descárgalo desde: https://visualstudio.microsoft.com/
- Selecciona "Desktop development with C++" durante la instalación
- Asegúrate de que incluye C++17

## Paso 2: Configurar vcpkg

```bash
# En tu carpeta de usuario o de desarrollo, clona vcpkg
git clone https://github.com/Microsoft/vcpkg.git
cd vcpkg
.\bootstrap-vcpkg.bat

# Espera a que termine (toma unos minutos)
```

### 2.1 Instalar dependencias

```bash
# Desde la carpeta de vcpkg
.\vcpkg install sdl2:x64-windows
.\vcpkg install opengl:x64-windows

# Esto descargará e instalará las librerías necesarias
```

## Paso 3: Clonar el Repositorio

```bash
cd C:\tus\carpetas
git clone https://github.com/alexflysss4-hash/bresenham-ui.git
cd bresenham-ui
```

## Paso 4: Clonar Dear ImGui

```bash
# Desde la carpeta bresenham-ui
git clone https://github.com/ocornut/imgui.git imgui
```

## Paso 5: Generar la Solución Visual Studio

### Opción A: Usar CMake GUI (Recomendado para principiantes)

1. Abre CMake GUI
2. En "Where is the source code:" → Selecciona `C:\...\bresenham-ui`
3. En "Where to build the binaries:" → Selecciona `C:\...\bresenham-ui\build`
4. Haz clic en **"Configure"**
5. Selecciona **"Visual Studio 16 2019"** (o tu versión)
6. En el siguiente paso, marca "Specify toolchain file for cross-compiling"
7. Selecciona la ruta: `C:\...\vcpkg\scripts\buildsystems\vcpkg.cmake`
8. Haz clic en "Configure" nuevamente
9. Haz clic en "Generate"
10. Haz clic en "Open Project"

### Opción B: Usar línea de comandos (PowerShell)

```powershell
# Navega a la carpeta del proyecto
cd C:\ruta\a\bresenham-ui

# Crea la carpeta build
mkdir build
cd build

# Genera la solución (reemplaza la ruta de vcpkg)
cmake .. -G "Visual Studio 16 2019" `
  -DCMAKE_TOOLCHAIN_FILE="C:\ruta\a\vcpkg\scripts\buildsystems\vcpkg.cmake"
```

## Paso 6: Compilar y Ejecutar

### En Visual Studio:

1. Se abrirá Visual Studio con la solución generada
2. En el menú superior, selecciona **"Release"** (no Debug para mejor rendimiento)
3. En "Solution Explorer", haz clic derecho en **"BresenhamUI"**
4. Selecciona **"Set as Startup Project"**
5. Presiona **F5** o haz clic en el botón de reproducción (Play)

### O desde PowerShell:

```powershell
cd bresenham-ui\build
cmake --build . --config Release
.\Release\BresenhamUI.exe
```

## Paso 7: Verificar que funciona

Si todo está bien, deberías ver:
- Una ventana con el título "Bresenham Algorithms - UI"
- Un panel de control a la derecha con opciones
- Un canvas negro a la izquierda para dibujar
- Opciones para seleccionar línea, círculo o círculo relleno
- Un selector de color

## Solución de Problemas

### Error: "sdl2.h not found"

**Solución:**
```bash
# Desde la carpeta vcpkg
.\vcpkg install sdl2:x64-windows
.\vcpkg integrate install
```

Luego reinicia Visual Studio.

### Error: "CMake generator not found"

Asegúrate de que Visual Studio 2019+ está instalado.

```bash
# Puedes ver los generadores disponibles con:
cmake --help
```

### Error durante la compilación: "undefined reference to SDL2"

- Verifica que vcpkg está integrado:
  ```bash
  .\vcpkg integrate install
  ```
- Reinicia Visual Studio después de ejecutar este comando

### La aplicación se cierra inmediatamente

- Verifica que todos los archivos existan (especialmente imgui/)
- Revisa la consola de Visual Studio para mensajes de error
- Asegúrate de compilar en **Release**, no en Debug

## Pasos Rápidos (Resumen)

1. Instala CMake y Visual Studio
2. Clona vcpkg e instala SDL2: `.\vcpkg install sdl2:x64-windows opengl:x64-windows`
3. Clona el repositorio
4. Clona imgui dentro del proyecto
5. Genera la solución con CMake (incluye la ruta de vcpkg)
6. Abre la solución en Visual Studio
7. Presiona F5 para ejecutar

## Recursos Útiles

- **CMake Docs**: https://cmake.org/documentation/
- **vcpkg GitHub**: https://github.com/Microsoft/vcpkg
- **Dear ImGui**: https://github.com/ocornut/imgui
- **SDL2**: https://www.libsdl.org/

¡Si todo está bien configurado, ¡ya puedes comenzar a dibujar! 🎨
