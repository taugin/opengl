/*
 * ModelShape.cpp
 *
 *  Created on: Jul 18, 2013
 *  Author: archermind
 */


#include "ModelShape.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define WindowWidth   mViewWidth//400
#define WindowHeight mViewHeight//400
#define BMP_Header_Length 54

static GLubyte* PixelData = NULL;

const char* ModelShape::RES_DIR = "res";
const char* ModelShape::SEPERATOR = "/";
const char* ModelShape::PIC_DIR = "pictures";
const char* ModelShape::BMP_DIR = "bmp";

ModelShape::ModelShape()
        : mViewWidth(0)
        , mViewHeight(0)
        , mRotateX(0)
        , mRotateY(0)
        , mRotateZ(0)
        , mButton(0)
        , mModelState(0)
        , mfovy(80)
        , mImageWidth(0)
        , mImageHeight(0) {
}

ModelShape::~ModelShape() {

}

void ModelShape::init() {
    DEBUG("ModelShape::init\n");
    glEnable(GL_DEPTH_TEST);
    glClear(GL_COLOR_BUFFER_BIT);
}

void ModelShape::draw() {

}

void ModelShape::setviewport(GLint width, GLint height) {
    mViewWidth = width;
    mViewHeight = height;
    //GLint iViewPort = width > height ? height : width;
    glViewport(0, 0, width, height);
    /*
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1,1,-1,1,-1,1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    DEBUG("mViewWidth = %d, mViewHeight = %d\n", mViewWidth, mViewHeight);
    */
}

void ModelShape::grab(void) {
    FILE* pDummyFile;
    FILE* pWritingFile;
    GLubyte* pPixelData;
    GLubyte BMP_Header[BMP_Header_Length];
    GLint i = 0;
    GLint j = 0;
    GLint PixelDataLength = 0;
    char fileName[256];

    i = WindowWidth * 3;
    while (i % 4 != 0)
        ++i;

    PixelDataLength = i * WindowHeight;

    pPixelData = (GLubyte*) malloc(PixelDataLength);
    if (pPixelData == 0)
        exit(0);

    memset(fileName, 0, sizeof(fileName));
    sprintf(fileName, "%s/%s/dummy.bmp", RES_DIR, BMP_DIR);
    printf("%s\n", fileName);
    pDummyFile = fopen(fileName, "rb");
    if (pDummyFile == 0) {
        perror("pDummyFile is NULL");
        exit(0);
    }

    memset(fileName, 0, sizeof(fileName));
    sprintf(fileName, "%s/%s/grab.bmp", RES_DIR, PIC_DIR);
    printf("%s\n", fileName);
    pWritingFile = fopen(fileName, "wb");
    if (pWritingFile == 0) {
        perror("pWritingFile is NULL");
        exit(0);
    }

    // Set the alignment
    glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
    glReadPixels(0, 0, WindowWidth, WindowHeight, GL_BGR_EXT, GL_UNSIGNED_BYTE,
            pPixelData);

    if (fread(BMP_Header, sizeof(BMP_Header), 1, pDummyFile) <=0) {
        DEBUG("read bmp header error\n");
        return ;
    }
    fwrite(BMP_Header, sizeof(BMP_Header), 1, pWritingFile);
    fseek(pWritingFile, 0x0012, SEEK_SET);
    i = WindowWidth;
    j = WindowHeight;
    DEBUG("i = %d, j = %d\n", i, j);
    fwrite(&i, sizeof(i), 1, pWritingFile);
    fwrite(&j, sizeof(j), 1, pWritingFile);

    fseek(pWritingFile, 0, SEEK_END);
    fwrite(pPixelData, PixelDataLength, 1, pWritingFile);

    fclose(pDummyFile);
    fclose(pWritingFile);
    free(pPixelData);
}

void ModelShape::readPixel() {
    GLint PixelLength;
    char fileName[256];
    memset(fileName, 0, sizeof(fileName));
    sprintf(fileName, "%s/%s/dummy.bmp", RES_DIR, BMP_DIR);
    DEBUG("%s\n", fileName);
    FILE* pFile = fopen(fileName, "rb");
    if(pFile == 0) {
        perror("pFile is NULL");
        exit(0);
    }

    fseek(pFile, 0x0012, SEEK_SET);
    if (fread(&mImageWidth, sizeof(mImageWidth), 1, pFile) <=0) {
        DEBUG("read image width error\n");
        return ;
    }
    if (fread(&mImageHeight, sizeof(mImageHeight), 1, pFile) <=0) {
        DEBUG("read image width error\n");
        return ;
    }
    DEBUG("mImageWidth = %d, mImageHeight = %d\n", mImageWidth, mImageHeight);
    PixelLength = mImageWidth * 3;
    while( PixelLength % 4 != 0 )
        ++PixelLength;
    PixelLength *= mImageHeight;

    PixelData = (GLubyte*)malloc(PixelLength);
    if( PixelData == 0 )
        exit(0);

    fseek(pFile, 54, SEEK_SET);
    if (fread(PixelData, PixelLength, 1, pFile) <=0) {
        DEBUG("read PixelData error\n");
        return ;
    }

    fclose(pFile);
}
void ModelShape::drawPixel() {
    glClear(GL_COLOR_BUFFER_BIT);
    if (PixelData == NULL) {
        return ;
    }
    glDrawPixels(mImageWidth, mImageHeight,
        GL_BGR_EXT, GL_UNSIGNED_BYTE, PixelData);
    glutSwapBuffers();
}

void ModelShape::setModelState(GLint state) {
    mModelState = state;
}

void ModelShape::changeRotateAngle(GLfloat angleX, GLfloat angleY, GLfloat angleZ) {
    mRotateX = mRotateX + angleX;
    mRotateY = mRotateY + angleY;
    mRotateZ = mRotateZ + angleZ;
}

void ModelShape::changeFovy(GLfloat fovy) {
    mfovy = mfovy + fovy;
    setviewport(mViewWidth, mViewHeight);
}

GLint ModelShape::state() {
    return mModelState;
}
