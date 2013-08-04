// OpenGL Class Implement

#include "Rect.h"


Rect::Rect() {

}

Rect::~Rect() {

}

void Rect::draw() {
    glClear(GL_COLOR_BUFFER_BIT);

    glRectf(-0.5f, -0.5f, 0.5f, 0.5f);

    glFlush();
    glutSwapBuffers();
}

