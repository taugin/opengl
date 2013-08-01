#include <GL/glut.h>
#include <stdio.h>

#include "Circle.h"
#include "OpenGLRender.h"
#include "Pentagon.h"
#include "Rect.h"
#include "Sine.h"
#include "Cube.h"
#include "Geometry.h"
#include "Car.h"
#include "Texture.h"


#define WINDOW_POSX 0
#define WINDOW_POSY 0
#define WINDOW_SIZEX 800
#define WINDOW_SIZEY 800

const char* strWindowTitle = "The First OpenGL Program";
static OpenGLRender* sOpenGLRender = NULL;

static void menuFunc(int menu) {
    if (sOpenGLRender == NULL) {
        perror("sOpenGLRender is NULL");
        return ;
    }
    sOpenGLRender->menuFunc(menu);
}

static void display() {
    if (sOpenGLRender == NULL) {
        perror("sOpenGLRender is NULL");
        return ;
    }
    sOpenGLRender->display();
}

static void reshape(GLint width, GLint height) {
    if (sOpenGLRender == NULL) {
        perror("sOpenGLRender is NULL");
        return ;
    }
    sOpenGLRender->reshape(width, height);
}

static void keyboardFunc(unsigned char c, int x, int y) {
    if (sOpenGLRender == NULL) {
        perror("sOpenGLRender is NULL");
        return ;
    }
    sOpenGLRender->keyboardFunc(c, x, y);
}

static void idle(void) {
    if (sOpenGLRender == NULL) {
        perror("sOpenGLRender is NULL");
        return ;
    }
    sOpenGLRender->idle();
}
static void mouseFunc(int button, int state, int x, int y) {
    if (sOpenGLRender == NULL) {
        perror("sOpenGLRender is NULL");
        return ;
    }
    sOpenGLRender->mouseFunc(button, state, x, y);
}

static void motionFunc(int x, int y) {
    if (sOpenGLRender == NULL) {
        perror("sOpenGLRender is NULL");
        return ;
    }
    sOpenGLRender->motionFunc(x, y);
}
static void createPopupMenu() {
    int menu;
    menu = glutCreateMenu(menuFunc);
    //glutAddMenuEntry("Red",0);
    //glutAttachMenu(GLUT_RIGHT_BUTTON);
}
static void displayVersion() {
    const GLubyte* name = glGetString(GL_VENDOR); //
    const GLubyte* biaoshifu = glGetString(GL_RENDERER); //
    const GLubyte* OpenGLVersion = glGetString(GL_VERSION); //
    const GLubyte* gluVersion = gluGetString(GLU_VERSION); //
    printf("OpenGL Vendor : %s\n", name);
    printf("Renderer : %s\n", biaoshifu);
    printf("OpenGL Version : %s\n", OpenGLVersion);
    printf("GLU Version : %s\n", gluVersion);
}
int main(int argc, char *argv[])
{
    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_RGBA | /*GLUT_SINGLE*/GLUT_DOUBLE);

    glutInitWindowPosition(WINDOW_POSX, WINDOW_POSY);

    glutInitWindowSize(WINDOW_SIZEX, WINDOW_SIZEY);

    glutCreateWindow(strWindowTitle);

    glutDisplayFunc(display);

    glutReshapeFunc(reshape);

    glutKeyboardFunc(keyboardFunc);

    glutMouseFunc(mouseFunc);

    glutMotionFunc(motionFunc);

    glutIdleFunc(idle);

    displayVersion();

    createPopupMenu();

    sOpenGLRender = new OpenGLRender();

    sOpenGLRender->init();

    glutMainLoop();

    delete sOpenGLRender;
    DEBUG("main function exit\n");
    return 0;

}
