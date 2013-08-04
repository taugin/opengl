// OpenGL Class Implement
#include <stdio.h>
#include "Car.h"
#include <math.h>
const int n = 1000;
const GLfloat R = 0.3f;
const GLfloat Pi = 3.1415926536f;

const GLfloat carouterP1[] = {-2.5, 0, 0.5};
const GLfloat carouterP2[] = {2, 0, 0.5};
const GLfloat carouterP3[] = {2, 1, 0.5};
const GLfloat carouterP4[] = {1, 1, 0.5};
const GLfloat carouterP5[] = {0.75, 1.5, 0.5};
const GLfloat carouterP6[] = {-0.75, 1.5, 0.5};
const GLfloat carouterP7[] = {-1, 1, 0.5};
const GLfloat carouterP8[] = {-2.5, 0.75, 0.5};

const GLfloat carinnerP1[] = {-2.5, 0, -0.5};
const GLfloat carinnerP2[] = {2, 0, -0.5};
const GLfloat carinnerP3[] = {2, 1, -0.5};
const GLfloat carinnerP4[] = {1, 1, -0.5};
const GLfloat carinnerP5[] = {0.75, 1.5, -0.5};
const GLfloat carinnerP6[] = {-0.75, 1.5, -0.5};
const GLfloat carinnerP7[] = {-1, 1, -0.5};
const GLfloat carinnerP8[] = {-2.5, 0.75, -0.5};

Car::Car() {

}

Car::~Car() {

}

void Car::init() {
    ModelShape::init();
}
void Car::setviewport(int width, int height) {
    ModelShape::setviewport(width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(mfovy, 1, 1, 21);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(1, 5, 5, 0, 0, 0, 0, 1, 0);
}
void Car::drawCar() {
    glPushMatrix();
    glColor3f(1, 1, 1);
    glBegin(GL_LINE_LOOP);
        glVertex3fv(carouterP1);
        glVertex3fv(carouterP2);
        glVertex3fv(carouterP3);
        glVertex3fv(carouterP4);
        glVertex3fv(carouterP5);
        glVertex3fv(carouterP6);
        glVertex3fv(carouterP7);
        glVertex3fv(carouterP8);
    glEnd();
    glBegin(GL_LINE_LOOP);
        glVertex3fv(carinnerP1);
        glVertex3fv(carinnerP2);
        glVertex3fv(carinnerP3);
        glVertex3fv(carinnerP4);
        glVertex3fv(carinnerP5);
        glVertex3fv(carinnerP6);
        glVertex3fv(carinnerP7);
        glVertex3fv(carinnerP8);
    glEnd();

    glBegin(GL_LINES);
        glVertex3fv(carouterP1);
        glVertex3fv(carinnerP1);
        glVertex3fv(carouterP2);
        glVertex3fv(carinnerP2);
        glVertex3fv(carouterP3);
        glVertex3fv(carinnerP3);
        glVertex3fv(carouterP4);
        glVertex3fv(carinnerP4);
        glVertex3fv(carouterP5);
        glVertex3fv(carinnerP5);
        glVertex3fv(carouterP6);
        glVertex3fv(carinnerP6);
        glVertex3fv(carouterP7);
        glVertex3fv(carinnerP7);
        glVertex3fv(carouterP8);
        glVertex3fv(carinnerP8);
    glEnd();
    glPopMatrix();
}
void Car::drawCoordinate() {
    glBegin(GL_LINES);
        glColor3f(1, 0, 0);
        glVertex3f(0, 0, 0);
        glVertex3f(5, 0, 0);

        glColor3f(0, 1, 0);
        glVertex3f(0, 0, 0);
        glVertex3f(0, 5, 0);

        glColor3f(0, 0, 1);
        glVertex3f(0, 0, 0);
        glVertex3f(0, 0, 10);
    glEnd();
    /*
    glBegin(GL_QUADS);
        //glColor3f(1, 1, 0);
        glVertex3f(-2, 0, 2);
        glVertex3f(2, 0, 2);
        glVertex3f(2, 0, -2);
        glVertex3f(-2, 0, -2);
    glEnd();
    glColor3f(1, 1, 1);
    */
}
void Car::drawCircle() {
    int i;
    glBegin(GL_LINE_LOOP);
    for (i = 0; i < n; ++i)
        glVertex2f(R * cos(2 * Pi / n * i), R * sin(2 * Pi / n * i));
    glEnd();
}

void Car::drawWheel() {
    glPushMatrix();
    glTranslatef(-1, 0, 0.5);
    drawCircle();

    glTranslatef(0, 0, -1);
    drawCircle();

    glTranslatef(2, 0, 0);
    drawCircle();

    glTranslatef(0, 0, 1);
    drawCircle();
    glPopMatrix();
}
void Car::draw() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glPushMatrix();
    glRotatef(mRotateX, 1, 0, 0);
    glRotatef(mRotateY, 0, 1, 0);
    glRotatef(mRotateZ, 0, 0, 1);
    drawCoordinate();
    drawWheel();
    drawCar();
    glPopMatrix();
    glutSwapBuffers();


}

