/*
 * OpenGLRender.cpp
 *
 *  Created on: Jul 18, 2013
 *  Author: archermind
 */


#include "OpenGLRender.h"
#include "ModelShape.h"
#include "Texture.h"
#include "Geometry.h"
#include "Car.h"
#include "Pentagon.h"

#include "Circle.h"
#include "Cube.h"
#include "Rect.h"
#include "Sine.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
static int count = 0;
OpenGLRender::OpenGLRender()
        : mModelShape(new Texture()){

    ModelShape *shape = new Car();
    mModelVector.push_back(shape);

    shape = new Circle();
    mModelVector.push_back(shape);

    shape = new Cube();
    mModelVector.push_back(shape);

    shape = new Geometry();
    mModelVector.push_back(shape);

    shape = new Rect();
    mModelVector.push_back(shape);

    shape = new Sine();
    mModelVector.push_back(shape);

    shape = new Texture();
    mModelVector.push_back(shape);
}

OpenGLRender::~OpenGLRender() {
    std::vector<ModelShape *>::iterator begin = mModelVector.begin();
    std::vector<ModelShape *>::iterator end = mModelVector.end();
    std::vector<ModelShape *>::iterator i;
    ModelShape* shape = NULL;
    for (i = begin;i != end; i++) {
        shape = *i;
        delete shape;
    }

}

void OpenGLRender::init() {
    DEBUG("OpenGLRender::init\n");
    mModelShape->init();
}

void OpenGLRender::display() {
    mModelShape->draw();
}

void OpenGLRender::reshape(int width, int height) {
    mModelShape->setviewport(width, height);
}

void OpenGLRender::idle() {

}

bool OpenGLRender::keyboardFunc(unsigned char c, int x, int y) {
    DEBUG("OpenGLRender::keyboardFunc : %c = %d, x = %d, y = %d\n", c, c, x, y);
    if (c == 'g' || c == 'G') {
        mModelShape->grab();
        return true;
    }else if (c == 27) {
        exit(0);
    }else if (c == 'x' || c == 'X') {
        mModelShape->setModelState(STATE_ROTATE_X);
        glutPostRedisplay();
        return true;
    } else if (c == 'y' || c == 'Y' ) {
        mModelShape->setModelState(STATE_ROTATE_Y);
        glutPostRedisplay();
        return true;
    } else if (c == 'z' || c == 'Z') {
        mModelShape->setModelState(STATE_ROTATE_Z);
        glutPostRedisplay();
        return true;
    } else if (c == 'u' || c == 'U') {
        if (mModelShape->state() == STATE_ROTATE_X) {
            mModelShape->changeRotateAngle(-1, 0, 0);
            glutPostRedisplay();
        } else if (mModelShape->state() == STATE_ROTATE_Y) {
            mModelShape->changeRotateAngle(0, -1, 0);
            glutPostRedisplay();
        } else if (mModelShape->state() == STATE_ROTATE_Z) {
            mModelShape->changeRotateAngle(0, 0, -1);
            glutPostRedisplay();
        } else if (mModelShape->state() == STATE_SCALE) {
            mModelShape->changeFovy(-1);
            glutPostRedisplay();
        }
        return true;
    } else if (c == 'd' || c == 'D') {
        if (mModelShape->state() == STATE_ROTATE_X) {
            mModelShape->changeRotateAngle(1, 0, 0);
            glutPostRedisplay();
        } else if (mModelShape->state() == STATE_ROTATE_Y) {
            mModelShape->changeRotateAngle(0, 1, 0);
            glutPostRedisplay();
        } else if (mModelShape->state() == STATE_ROTATE_Z) {
            mModelShape->changeRotateAngle(0, 0, 1);
            glutPostRedisplay();
        } else if (mModelShape->state() == STATE_SCALE) {
            mModelShape->changeFovy(1);
            glutPostRedisplay();
        }
        return true;
    } else if (c == 's' || c == 'S') {
        mModelShape->setModelState(STATE_SCALE);
        glutPostRedisplay();
        return true;
    } else if (c == 'q' || c == 'Q') {
        mModelShape->setModelState(STATE_QUIT);
        glutPostRedisplay();
        return true;
    } else if (c == 'c' || c == 'C') {
        int index = count ++ % mModelVector.size();
        mModelShape = mModelVector[index];
        mModelShape->init();
//        mModelShape->setviewport();
        glutPostRedisplay();
    }
    return false;
}

void OpenGLRender::motionFunc(int x, int y) {
    DEBUG("OpenGLRender::motionFunc x = %d, y = %d\n", x, y);
}
void OpenGLRender::mouseFunc(int button, int state, int x, int y) {
    DEBUG("ModelShape::mouseFunc button : %d, state : %d, x : %d, y : %d\n", button, state, x, y);
    if (button == GLUT_LEFT_BUTTON) {
        if (state == GLUT_UP) {
            mModelShape->changeFovy(1);
            glutPostRedisplay();
        }
    } else if (button == GLUT_RIGHT_BUTTON) {
        if (state == GLUT_UP) {
            mModelShape->changeFovy(-1);
            glutPostRedisplay();
        }
    }else if (button == GLUT_MIDDLE_BUTTON) {
        if (state == GLUT_UP) {
            mModelShape->changeFovy(-1);
            glutPostRedisplay();
        }
    }
}

void OpenGLRender::menuFunc(int menu) {

}
