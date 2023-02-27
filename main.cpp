#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <cmath>
#include "Rectangle.h"
#include <GLFW/glfw3.h>

int window;

struct Point {
    GLint x;
    GLint y;
};

void draw_dda(Point p1, Point p2) {
    GLfloat dx = p2.x - p1.x;
    GLfloat dy = p2.y - p1.y;

    GLfloat x1 = p1.x;
    GLfloat y1 = p1.y;

    GLfloat step = 0;

    if(abs(dx) > abs(dy)) {
        step = abs(dx);
    } else {
        step = abs(dy);
    }

    GLfloat xInc = dx/step;
    GLfloat yInc = dy/step;

    for(float i = 1; i <= step; i++) {
        glVertex2i(x1, y1);
        x1 += xInc;
        y1 += yInc;
    }
}

void init() {
    glClearColor(0.2, 0.2, 0.2, 0.0);
    glColor3f(1.0f, 1.0f, 1.0f);
    glPointSize(1.0f);
    gluOrtho2D(0.0, 640, 0.0, 480);
}

void closeWindowFunction() {
    glutDestroyWindow(window);
}

void drawRect(int width, int heigh, int x, int y)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.0,0.0,1.0);
    glLineWidth(30);

    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    glBegin(GL_POLYGON);
    glVertex2i(x,y);
    glVertex2i(x+width,y);
    glVertex2i(x+width,y+heigh);
    glVertex2i(x, y+heigh);
    glEnd();

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    glFlush();
}

void display(void) {
             // Sqaure Coordinates
    Point   p1 = {200, 200},
            p2 = {400, 200},
            p3 = {400, 400},
            p4 = {200, 400},
             // Inside diagnol square
            p5 = {200, 300},
            p6 = {400, 200},
            p7 = {400, 300},
            p8 = {400, 400};

    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_POINTS);

    // External Square
//    draw_dda(p1, p2);
//    draw_dda(p2, p3);
//    draw_dda(p3, p4);
//    draw_dda(p4, p1);
//
//    // Internal Square
//    draw_dda(p5, p6);
//    draw_dda(p6, p7);
//    draw_dda(p7, p8);
//    draw_dda(p8, p5);

    int x = 10;
    int y = 10;
    int w = 5;
    int h = 2;

    glEnd();

    glBegin(GL_QUADS);

    int width, height;
    glfwGetWindowSize(glfwGetCurrentContext() ,&width, &height);
    Rectangle rectangle(100,100,width/2,height/2,70, 0.3f,0.42f,0.18f);
    rectangle.draw();

//    glVertex3f(x,y,0);
//    glVertex3f(x+w,y,0);
//    glVertex3f(x+w,y+h,0);
//    glVertex3f(x,y+h,0);


    glEnd();
    glFlush();

}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutInitWindowPosition(200, 200);
    glutInitWindowSize(640, 480);
    window = glutCreateWindow("Square");
    glutDisplayFunc(display);
    glutWMCloseFunc(closeWindowFunction);
    init();
    glutMainLoop();

    return 0;
}

