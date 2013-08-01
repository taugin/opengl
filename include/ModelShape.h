/*
 * ModelShape.h
 *
 *  Created on: Jul 18, 2013
 *      Author: archermind
 */

#ifndef MODELSHAPE_H_
#define MODELSHAPE_H_
#include <GL/glut.h>
#include <stdio.h>

#define _DEBUG
#ifdef _DEBUG
    #define DEBUG(format, args...) printf(format, ##args)
#else
    #define DEBUG(format, args...) (void)0
#endif


enum _State {
    STATE_ROTATE_X = 1,
    STATE_ROTATE_Y,
    STATE_ROTATE_Z,
    STATE_SCALE,
    STATE_QUIT
};

class ModelShape {
public:
    static const char* RES_DIR;
    static const char* SEPERATOR;
    static const char* PIC_DIR;
    static const char* BMP_DIR;
public:
    ModelShape();
    virtual ~ModelShape();

    virtual void init();
    virtual void draw();
    virtual void setviewport(GLint width, GLint height);

    void setModelState(GLint state);
    void changeRotateAngle(GLfloat angleX, GLfloat angleY, GLfloat angleZ);
    void changeFovy(GLfloat fovy);

    void grab(void);
    void readPixel();
    void drawPixel();
    GLint state();

protected:
    GLint mViewWidth;
    GLint mViewHeight;
    GLfloat mRotateX;
    GLfloat mRotateY;
    GLfloat mRotateZ;
    GLint mButton;
    GLint mModelState;
    GLfloat mfovy;

private:
    GLint mImageWidth;
    GLint mImageHeight;
};

#endif /* MODELSHAPE_H_ */
