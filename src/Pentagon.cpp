// OpenGL Class Implement

#include <math.h>
#include "Pentagon.h"

const static GLfloat Pi = 3.1415926536f;
Pentagon::Pentagon() {

}

Pentagon::~Pentagon() {

}

void Pentagon::draw() {
    GLfloat a = 1 / (2-2*cos(72*Pi/180));
    GLfloat bx = a * cos(18 * Pi/180);
    GLfloat by = a * sin(18 * Pi/180);
    GLfloat cy = -a * cos(18 * Pi/180);
    GLfloat
        PointA[2] = { 0, a },
        PointB[2] = { bx, by },
        PointC[2] = { 0.5, cy },
        PointD[2] = { -0.5, cy },
        PointE[2] = { -bx, by };

    glClear(GL_COLOR_BUFFER_BIT);
    //
    glBegin(GL_LINE_LOOP);
        glVertex2fv(PointA);
        glVertex2fv(PointC);
        glVertex2fv(PointE);
        glVertex2fv(PointB);
        glVertex2fv(PointD);
    glEnd();
    glFlush();
    glutSwapBuffers();
}

