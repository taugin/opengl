// OpenGL Class Implement

#include <stdio.h>
#include <math.h>
#include "Circle.h"

const static int n = 20;
const static GLfloat R = 0.5f;
const static GLfloat Pi = 3.1415926536f;
Circle::Circle() {

}

Circle::~Circle() {

}

void Circle::init() {
    ModelShape::init();
}

void Circle::draw() {
    DEBUG("Circle::draw\n");
    int i;
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_POLYGON);
    for(i=0; i<n; ++i)
        glVertex2f(R*cos(2*Pi/n*i), R*sin(2*Pi/n*i));
    glEnd();
    glutSwapBuffers();
}

