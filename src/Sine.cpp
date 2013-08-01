// OpenGL Class Implement

#include <math.h>
#include "Sine.h"

const static GLfloat factor = 0.1f;
Sine::Sine() {

}

Sine::~Sine() {

}

void Sine::draw() {
    GLfloat x;
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_LINES);
        glVertex2f(-1.0f, 0.0f);
        glVertex2f(1.0f, 0.0f);         //
        glVertex2f(0.0f, -1.0f);
        glVertex2f(0.0f, 1.0f);         //
    glEnd();
    glBegin(GL_LINE_STRIP);
    for(x=-1.0f/factor; x<1.0f/factor; x+=0.01f)
    {
        glVertex2f(x*factor, sin(x)*factor);
    }
    glEnd();
    glFlush();
    glutSwapBuffers();
}

