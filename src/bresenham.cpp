#include "../include/bresenham.h"
#include <cmath>
#include <algorithm>

// Algoritmo de línea de Bresenham
std::vector<Point> BresenhamAlgorithms::drawLine(int x0, int y0, int x1, int y1) {
    std::vector<Point> points;
    
    int dx = std::abs(x1 - x0);
    int dy = std::abs(y1 - y0);
    int sx = (x0 < x1) ? 1 : -1;
    int sy = (y0 < y1) ? 1 : -1;
    int err = dx - dy;
    
    int x = x0, y = y0;
    
    while (true) {
        points.push_back({x, y});
        
        if (x == x1 && y == y1) break;
        
        int e2 = 2 * err;
        if (e2 > -dy) {
            err -= dy;
            x += sx;
        }
        if (e2 < dx) {
            err += dx;
            y += sy;
        }
    }
    
    return points;
}

// Algoritmo de círculo de Bresenham
std::vector<Point> BresenhamAlgorithms::drawCircle(int xc, int yc, int radius) {
    std::vector<Point> points;
    
    int x = radius;
    int y = 0;
    int d = 3 - 2 * radius;
    
    auto addCirclePoints = [&](int x, int y) {
        points.push_back({xc + x, yc + y});
        points.push_back({xc - x, yc + y});
        points.push_back({xc + x, yc - y});
        points.push_back({xc - x, yc - y});
        points.push_back({xc + y, yc + x});
        points.push_back({xc - y, yc + x});
        points.push_back({xc + y, yc - x});
        points.push_back({xc - y, yc - x});
    };
    
    while (y <= x) {
        addCirclePoints(x, y);
        
        if (d <= 0) {
            d = d + 4 * y + 6;
        } else {
            d = d + 4 * (y - x) + 10;
            x--;
        }
        y++;
    }
    
    return points;
}

// Relleno de círculo
std::vector<Point> BresenhamAlgorithms::fillCircle(int xc, int yc, int radius) {
    std::vector<Point> points;
    
    for (int r = 0; r <= radius; r++) {
        std::vector<Point> circlePoints = drawCircle(xc, yc, r);
        for (const auto& p : circlePoints) {
            points.push_back(p);
        }
    }
    
    return points;
}
