#include <GL/glut.h>
#include <math.h>
#include <vector>
#include <iostream>
using namespace std;
struct Point {
    int x, y;
};
vector<Point> bresenhamCircle(int xc, int yc, int r) {
    vector<Point> points;
    int x = 0, y = r;
    int d = 3 - 2 * r;

    auto addPoints = [&](int xc, int yc, int x, int y) {
        points.push_back({ xc + x, yc + y });
        points.push_back({ xc - x, yc + y });
        points.push_back({ xc + x, yc - y });
        points.push_back({ xc - x, yc - y });
        points.push_back({ xc + y, yc + x });
        points.push_back({ xc - y, yc + x });
        points.push_back({ xc + y, yc - x });
        points.push_back({ xc - y, yc - x });
        };

    addPoints(xc, yc, x, y);
    while (y >= x) {
        x++;
        if (d > 0) {
            y--;
            d = d + 4 * (x - y) + 10;
        }
        else {
            d = d + 4 * x + 6;
        }
        addPoints(xc, yc, x, y);
    }
    return points;
}
void drawSpirographSAUMYA(int numCircles, int radius, int separation) {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.0, 0.0, 0.0);
    glBegin(GL_POINTS);

    for (int i = 0; i < numCircles; ++i) {
        float angle = 2.0f * 22/7 * i / numCircles;
        int xc = separation * cos(angle);
        int yc = separation * sin(angle);

        vector<Point> circle = bresenhamCircle(xc, yc, radius);
        for (const auto& point : circle) {
            glVertex2i(point.x, point.y);
        }
    }

    glEnd();
    glFlush();
}

// OpenGL display function
void display() {
    int numCircles = 50;    // Number of circles
    int radius = 190;        // Radius of the circles
    int separation = 150;   // Distance between centers

    drawSpirographSAUMYA(numCircles, radius, separation);
}

void init() {
    glClearColor(1.0, 1.0, 1.0, 1.0);  // White background
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(-500, 500, -500, 500);  // Set coordinate system
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(800, 800);
    glutCreateWindow("Spirograph using Bresenham's Circle Algorithm SAUMYA");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}







