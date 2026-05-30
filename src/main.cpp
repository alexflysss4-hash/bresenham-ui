#include <SDL2/SDL.h>
#include <GL/gl.h>
#include <imgui.h>
#include <imgui_impl_sdl2.h>
#include <imgui_impl_opengl3.h>
#include <vector>
#include <iostream>
#include "../include/bresenham.h"

// Variables globales
struct Shape {
    std::vector<Point> points;
    Color color;
    int type; // 0 = línea, 1 = círculo, 2 = círculo relleno
};

std::vector<Shape> shapes;
Color currentColor(255, 255, 255, 255);
bool drawing = false;
int drawMode = 0; // 0 = línea, 1 = círculo, 2 = círculo relleno
Point startPoint = {0, 0};
int brushRadius = 20;

// Canvas
const int CANVAS_WIDTH = 800;
const int CANVAS_HEIGHT = 600;

void drawPixel(int x, int y, const Color& color) {
    glPointSize(2.0f);
    glBegin(GL_POINTS);
    glColor4f(color.r / 255.0f, color.g / 255.0f, color.b / 255.0f, color.a / 255.0f);
    glVertex2f(x - CANVAS_WIDTH / 2.0f, CANVAS_HEIGHT / 2.0f - y);
    glEnd();
}

void renderCanvas() {
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    glOrtho(-CANVAS_WIDTH / 2.0f, CANVAS_WIDTH / 2.0f, -CANVAS_HEIGHT / 2.0f, CANVAS_HEIGHT / 2.0f, -1.0f, 1.0f);
    
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
    
    glClear(GL_COLOR_BUFFER_BIT);
    
    // Dibujar canvas de fondo
    glBegin(GL_QUADS);
    glColor3f(0.1f, 0.1f, 0.1f);
    glVertex2f(-CANVAS_WIDTH / 2.0f, -CANVAS_HEIGHT / 2.0f);
    glVertex2f(CANVAS_WIDTH / 2.0f, -CANVAS_HEIGHT / 2.0f);
    glVertex2f(CANVAS_WIDTH / 2.0f, CANVAS_HEIGHT / 2.0f);
    glVertex2f(-CANVAS_WIDTH / 2.0f, CANVAS_HEIGHT / 2.0f);
    glEnd();
    
    // Dibujar todas las figuras
    for (const auto& shape : shapes) {
        for (const auto& point : shape.points) {
            drawPixel(point.x, point.y, shape.color);
        }
    }
    
    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
}

int main(int, char**) {
    // Setup window
    SDL_SetHint(SDL_HINT_IME_SHOW_UI, "0");
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        fprintf(stderr, "Error: SDL_Init failed. %s\n", SDL_GetError());
        return -1;
    }

    // Decide GL+GLSL versions
    const char* glsl_version = "#version 150";
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);

    // Create window with graphics context
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
    SDL_Window* window = SDL_CreateWindow(
        "Bresenham Algorithms - UI",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        1400,
        700,
        SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN
    );
    if (window == nullptr) {
        fprintf(stderr, "Error: SDL_CreateWindow failed. %s\n", SDL_GetError());
        SDL_Quit();
        return -1;
    }

    SDL_GLContext gl_context = SDL_GL_CreateContext(window);
    if (gl_context == nullptr) {
        fprintf(stderr, "Error: Failed to create OpenGL context. %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return -1;
    }
    SDL_GL_MakeCurrent(window, gl_context);
    SDL_GL_SetSwapInterval(1); // Enable vsync

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    ImGui::StyleColorsDark();

    // Setup Platform/Renderer backends
    ImGui_ImplSDL2_InitForOpenGL(window, gl_context);
    ImGui_ImplOpenGL3_Init(glsl_version);

    ImVec4 clear_color = ImVec4(0.1f, 0.1f, 0.1f, 1.00f);
    bool done = false;

    // Main loop
    while (!done) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            ImGui_ImplSDL2_ProcessEvent(&event);
            if (event.type == SDL_QUIT)
                done = true;
            if (event.type == SDL_WINDOWEVENT && event.window.event == SDL_WINDOWEVENT_CLOSE && event.window.windowID == SDL_GetWindowID(window))
                done = true;
            
            if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT) {
                int mouse_x = event.button.x;
                int mouse_y = event.button.y;
                
                if (mouse_x > 50 && mouse_x < 850 && mouse_y > 50 && mouse_y < 650) {
                    drawing = true;
                    startPoint = {mouse_x - 50, mouse_y - 50};
                }
            }
            if (event.type == SDL_MOUSEBUTTONUP && event.button.button == SDL_BUTTON_LEFT) {
                if (drawing) {
                    int mouse_x = event.button.x;
                    int mouse_y = event.button.y;
                    
                    if (mouse_x > 50 && mouse_x < 850 && mouse_y > 50 && mouse_y < 650) {
                        Point endPoint = {mouse_x - 50, mouse_y - 50};
                        Shape newShape;
                        newShape.color = currentColor;
                        newShape.type = drawMode;
                        
                        if (drawMode == 0) { // Línea
                            newShape.points = BresenhamAlgorithms::drawLine(
                                startPoint.x, startPoint.y,
                                endPoint.x, endPoint.y
                            );
                        } else if (drawMode == 1) { // Círculo
                            int radius = static_cast<int>(std::sqrt(
                                (endPoint.x - startPoint.x) * (endPoint.x - startPoint.x) +
                                (endPoint.y - startPoint.y) * (endPoint.y - startPoint.y)
                            ));
                            newShape.points = BresenhamAlgorithms::drawCircle(
                                startPoint.x, startPoint.y, radius
                            );
                        } else if (drawMode == 2) { // Círculo relleno
                            int radius = static_cast<int>(std::sqrt(
                                (endPoint.x - startPoint.x) * (endPoint.x - startPoint.x) +
                                (endPoint.y - startPoint.y) * (endPoint.y - startPoint.y)
                            ));
                            newShape.points = BresenhamAlgorithms::fillCircle(
                                startPoint.x, startPoint.y, radius
                            );
                        }
                        
                        shapes.push_back(newShape);
                    }
                    drawing = false;
                }
            }
        }

        // Start Dear ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplSDL2_NewFrame();
        ImGui::NewFrame();

        // Control Panel
        ImGui::SetNextWindowPos(ImVec2(900, 20), ImGuiCond_FirstUseEver);
        ImGui::SetNextWindowSize(ImVec2(460, 660), ImGuiCond_FirstUseEver);
        ImGui::Begin("Control Panel", nullptr, ImGuiWindowFlags_NoMove);
        
        ImGui::Text("=== Drawing Mode ===");
        ImGui::RadioButton("Línea Bresenham", &drawMode, 0);
        ImGui::RadioButton("Círculo Bresenham", &drawMode, 1);
        ImGui::RadioButton("Círculo Relleno", &drawMode, 2);
        
        ImGui::Separator();
        ImGui::Text("=== Color ===");
        
        static float col[4] = {1.0f, 1.0f, 1.0f, 1.0f};
        if (ImGui::ColorEdit4("Color de Dibujo", col)) {
            currentColor.r = static_cast<uint8_t>(col[0] * 255);
            currentColor.g = static_cast<uint8_t>(col[1] * 255);
            currentColor.b = static_cast<uint8_t>(col[2] * 255);
            currentColor.a = static_cast<uint8_t>(col[3] * 255);
        }
        
        ImGui::Separator();
        ImGui::Text("=== Instrucciones ===");
        ImGui::BulletText("Selecciona el tipo de figura");
        ImGui::BulletText("Elige el color deseado");
        ImGui::BulletText("Haz clic y arrastra en el canvas");
        ImGui::BulletText("Para línea: punto inicial a punto final");
        ImGui::BulletText("Para círculo: centro y punto en el borde");
        
        ImGui::Separator();
        ImGui::Text("=== Figuras Dibujadas ===");
        ImGui::Text("Total: %zu", shapes.size());
        
        if (ImGui::Button("Limpiar Canvas", ImVec2(-1, 0))) {
            shapes.clear();
        }
        
        ImGui::Separator();
        ImGui::Text("Figuras en el canvas:");
        for (size_t i = 0; i < shapes.size(); ++i) {
            ImGui::Text("Figura %zu - Color: RGB(%d, %d, %d)",
                i + 1, shapes[i].color.r, shapes[i].color.g, shapes[i].color.b);
        }
        
        ImGui::End();

        // Canvas Window
        ImGui::SetNextWindowPos(ImVec2(20, 20), ImGuiCond_FirstUseEver);
        ImGui::SetNextWindowSize(ImVec2(850, 660), ImGuiCond_FirstUseEver);
        ImGui::Begin("Canvas", nullptr, ImGuiWindowFlags_NoMove);
        
        ImDrawList* draw_list = ImGui::GetWindowDrawList();
        ImVec2 canvas_pos = ImGui::GetCursorScreenPos();
        ImVec2 canvas_size = ImGui::GetContentRegionAvail();
        
        draw_list->AddRectFilled(
            canvas_pos,
            ImVec2(canvas_pos.x + CANVAS_WIDTH, canvas_pos.y + CANVAS_HEIGHT),
            IM_COL32(25, 25, 25, 255)
        );
        
        // Dibujar figuras en el canvas ImGui
        for (const auto& shape : shapes) {
            ImU32 col = IM_COL32(shape.color.r, shape.color.g, shape.color.b, shape.color.a);
            for (const auto& point : shape.points) {
                draw_list->AddCircleFilled(
                    ImVec2(canvas_pos.x + point.x, canvas_pos.y + point.y),
                    1.5f,
                    col
                );
            }
        }
        
        ImGui::InvisibleButton("canvas", ImVec2(CANVAS_WIDTH, CANVAS_HEIGHT));
        
        ImGui::End();

        // Rendering
        ImGui::Render();
        glViewport(0, 0, (int)io.DisplaySize.x, (int)io.DisplaySize.y);
        glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w);
        glClear(GL_COLOR_BUFFER_BIT);

        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        SDL_GL_SwapWindow(window);
    }

    // Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();

    SDL_GL_DeleteContext(gl_context);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
