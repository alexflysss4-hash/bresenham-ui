#pragma once
#include <vector>
#include <cstdint>

struct Point {
    int x, y;
};

struct Color {
    uint8_t r, g, b, a;
    Color(uint8_t r = 255, uint8_t g = 255, uint8_t b = 255, uint8_t a = 255)
        : r(r), g(g), b(b), a(a) {}
};

class BresenhamAlgorithms {
public:
    // Algoritmo de línea de Bresenham
    static std::vector<Point> drawLine(int x0, int y0, int x1, int y1);
    
    // Algoritmo de círculo de Bresenham
    static std::vector<Point> drawCircle(int xc, int yc, int radius);
    
    // Relleno de círculo (completo)
    static std::vector<Point> fillCircle(int xc, int yc, int radius);
};
