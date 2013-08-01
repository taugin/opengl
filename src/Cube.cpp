// OpenGL Class Implement

#include <stdio.h>

#include "Cube.h"

#define EDGE 1
Cube::Cube() {

}

Cube::~Cube() {

}

void Cube::draw() {
    DEBUG("Cube::draw\n");
    GLfloat point1[] = {0, 0, 0};
    GLfloat point2[] = {EDGE, 0, 0};
    GLfloat point3[] = {EDGE, EDGE, 0};
    GLfloat point4[] = {0, EDGE, 0};
    GLfloat point5[] = {0, 0, EDGE};
    GLfloat point6[] = {EDGE, 0, EDGE};
    GLfloat point7[] = {EDGE, EDGE, EDGE};
    GLfloat point8[] = {0, EDGE, EDGE};

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    //printf("mViewWidth = %d, mViewHeight = %d\n", mViewWidth, mViewHeight);
    gluPerspective(40.0f, 1, 1, 20);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(5, 5, 10, 0, 0, 0, 0, 1, 0);


    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_LINE_LOOP);
        glVertex3fv(point1);
        glVertex3fv(point2);
        glVertex3fv(point3);
        glVertex3fv(point4);
    glEnd();

    glBegin(GL_LINE_LOOP);
        glVertex3fv(point2);
        glVertex3fv(point3);
        glVertex3fv(point7);
        glVertex3fv(point6);
    glEnd();

    glBegin(GL_LINE_LOOP);
        glVertex3fv(point3);
        glVertex3fv(point4);
        glVertex3fv(point8);
        glVertex3fv(point7);
    glEnd();

    glBegin(GL_LINE_LOOP);
        glVertex3fv(point1);
        glVertex3fv(point4);
        glVertex3fv(point8);
        glVertex3fv(point5);
    glEnd();

    glBegin(GL_LINE_LOOP);
        glVertex3fv(point5);
        glVertex3fv(point6);
        glVertex3fv(point7);
        glVertex3fv(point8);
    glEnd();

    glBegin(GL_LINE_LOOP);
        glVertex3fv(point1);
        glVertex3fv(point5);
        glVertex3fv(point6);
        glVertex3fv(point2);
    glEnd();
    glutSwapBuffers();
}

