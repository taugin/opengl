/*
 * OpenGLRender.h
 *
 *  Created on: Jul 18, 2013
 *      Author: archermind
 */

#ifndef OPENGLRENDER_H_
#define OPENGLRENDER_H_
#include <GL/glut.h>
#include <vector>

class ModelShape;

class OpenGLRender {
public:
    static const char* RES_DIR;
    static const char* SEPERATOR;
    static const char* PIC_DIR;
public:
    OpenGLRender();
    ~OpenGLRender();

    void init();
    void display();
    void reshape(int width, int height);
    void idle();
    bool keyboardFunc(unsigned char c, int x, int y);
    void mouseFunc(int button, int state, int x, int y);
    void motionFunc(int x, int y);
    void menuFunc(int menu);

private:
    ModelShape* mModelShape;

    //ModelShape* mModelShapes[]
    std::vector<ModelShape*> mModelVector;
};

#endif /* OpenGLRender_H_ */
