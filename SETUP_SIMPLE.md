# Setup Simplificado - SIN vcpkg

## Opción MÁS FÁCIL: Instalación Manual de Librerías

### Paso 1: Descargar SDL2

1. Ve a: https://www.libsdl.org/download-2.0.php
2. Descarga: **SDL2-devel-2.28.x-VC.zip** (para Visual Studio Windows)
3. Extrae en: **C:\SDL2** (crea la carpeta si no existe)

Verifica que veas estas carpetas en C:\SDL2:
- `include/` (contiene SDL.h)
- `lib/` (contiene .lib files)

### Paso 2: Descargar Dear ImGui

```bash
# Desde tu carpeta del proyecto
cd BresenhamGUIh
git clone https://github.com/ocornut/imgui.git imgui
```

### Paso 3: Actualizar el proyecto

```bash
git pull origin main
```

### Paso 4: Generar la solución (SIN vcpkg)

```powershell
cd C:\Users\ssale\OneDrive\Escritorio\BresenhamGUIh
rmdir build /s /q
mkdir build
cd build

# Usa este comando SIN toolchain
cmake .. -G "Visual Studio 16 2019"
```

### Paso 5: Abrir en Visual Studio

```bash
BresenhamUI.sln
```

Luego compila (F5).

---

## Si Sale Error de SDL2

En Visual Studio:
1. Click derecho en **BresenhamUI**
2. **Properties**
3. **VC++ Directories**
4. En **Include Directories**, agrega: `C:\SDL2\include`
5. En **Library Directories**, agrega: `C:\SDL2\lib\x64`
6. **Apply** → OK
7. Vuelve a compilar (F5)

---

## Alternativa: Usar vcpkg (Si quieres)

Si prefieres usar vcpkg es más automático:

```powershell
# En PowerShell, clona vcpkg en C:\
git clone https://github.com/Microsoft/vcpkg.git C:\vcpkg
cd C:\vcpkg
.\bootstrap-vcpkg.bat

# Instala las librerías
.\vcpkg install sdl2:x64-windows opengl:x64-windows
.\vcpkg integrate install

# Luego regresa al proyecto
cd C:\Users\ssale\OneDrive\Escritorio\BresenhamGUIh
rmdir build /s /q
mkdir build
cd build

cmake .. -G "Visual Studio 16 2019" -DCMAKE_TOOLCHAIN_FILE="C:\vcpkg\scripts\buildsystems\vcpkg.cmake"
```

---

Usa la **opción más fácil** para ti. ¿Cuál prefieres? 🎯
