// OpenGL Class Implement

#include "Geometry.h"

static int day = 200; // day鐨勫彉鍖栵細浠�0鍒�359
Geometry::Geometry() {

}

Geometry::~Geometry() {

}

void Geometry::draw() {
    glPushMatrix();
    DEBUG("mRotateX = %f, mRotateY = %f, mRotateZ = %f\n", mRotateX, mRotateY, mRotateZ);
    glRotatef(mRotateX, 1, 0, 0);
    glRotatef(mRotateY, 0, 1, 0);
    glRotatef(mRotateZ, 0, 0, 1);
    //drawLines();
    //reversal();
    //globeModel();
    lightGlobalModel();
    glPopMatrix();
    glutSwapBuffers();
}
void Geometry::drawLines() {
    glClear(GL_COLOR_BUFFER_BIT);
    glEnable(GL_LINE_STIPPLE);
    glLineWidth(10.0f);
    glLineStipple(2, 0x0F0F);
    glBegin(GL_LINES);
        glVertex3f(0, 0, 0);
        glVertex3f(1, 0, 0);

        glVertex3f(0, 0, 0);
        glVertex3f(-1, 0, 0);

        glVertex3f(0, 0, 0);
        glVertex3f(0, 1, 0);

        glVertex3f(0, 0, 0);
        glVertex3f(0, -1, 0);
    glEnd();
    glFlush();
}
void Geometry::drawPoints() {

}
void Geometry::drawLineStipple() {

}

void Geometry::reversal() {
    glClear(GL_COLOR_BUFFER_BIT);

    glPolygonMode(GL_FRONT, GL_FILL); // 璁剧疆姝ｉ潰涓哄～鍏呮ā寮�

    glPolygonMode(GL_BACK, GL_LINE);   // 璁剧疆鍙嶉潰涓虹嚎褰㈡ā寮�

    glFrontFace(GL_CCW);               // 璁剧疆閫嗘椂閽堟柟鍚戜负姝ｉ潰

    glBegin(GL_POLYGON);               // 鎸夐�嗘椂閽堢粯鍒朵竴涓鏂瑰舰锛屽湪宸︿笅鏂�

        glVertex2f(-0.5f, -0.5f);

        glVertex2f(0.0f, -0.5f);

        glVertex2f(0.0f, 0.0f);

        glVertex2f(-0.5f, 0.0f);

    glEnd();

    glBegin(GL_POLYGON);               // 鎸夐『鏃堕拡缁樺埗涓�涓鏂瑰舰锛屽湪鍙充笂鏂�

        glVertex2f(0.0f, 0.0f);

        glVertex2f(0.0f, 0.5f);

        glVertex2f(0.5f, 0.5f);

        glVertex2f(0.5f, 0.0f);

    glEnd();

    glFlush();
}

void Geometry::globeModel() {
    glEnable(GL_DEPTH_TEST);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(75, 1, 1, 400000000);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0, -200000000, 200000000, 0, 0, 0, 0, 0, 1);

    // 缁樺埗绾㈣壊鐨勨�滃お闃斥��
    glColor3f(1.0f, 0.0f, 0.0f);
    glutSolidSphere(69600000, 20, 20);

    // 缁樺埗钃濊壊鐨勨�滃湴鐞冣��
    glColor3f(0.0f, 0.0f, 1.0f);
    glRotatef(day/360.0*360.0, 0.0f, 0.0f, -1.0f);
    glTranslatef(150000000, 0.0f, 0.0f);
    glutSolidSphere(15945000, 20, 20);

    // 缁樺埗榛勮壊鐨勨�滄湀浜��
    glColor3f(1.0f, 1.0f, 0.0f);
    glRotatef(day/30.0*360.0 - day/360.0*360.0, 0.0f, 0.0f, -1.0f);
    glTranslatef(38000000, 0.0f, 0.0f);
    glutSolidSphere(4345000, 20, 20);

    glFlush();
}

void Geometry::lightGlobalModel() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // 鍒涘缓閫忚鏁堟灉瑙嗗浘
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(90.0f, 1.0f, 1.0f, 20.0f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0.0, 5.0, -10.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

    // 瀹氫箟澶槼鍏夋簮锛屽畠鏄竴绉嶇櫧鑹茬殑鍏夋簮
    {
    GLfloat sun_light_position[] = {0.0f, 0.0f, 0.0f, 1.0f};
    GLfloat sun_light_ambient[]   = {0.0f, 0.0f, 0.0f, 1.0f};
    GLfloat sun_light_diffuse[]   = {1.0f, 1.0f, 1.0f, 1.0f};
    GLfloat sun_light_specular[] = {1.0f, 1.0f, 1.0f, 1.0f};

    glLightfv(GL_LIGHT0, GL_POSITION, sun_light_position);
    glLightfv(GL_LIGHT0, GL_AMBIENT,   sun_light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE,   sun_light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, sun_light_specular);

    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHTING);
    glEnable(GL_DEPTH_TEST);
    }

    // 瀹氫箟澶槼鐨勬潗璐ㄥ苟缁樺埗澶槼
    {
        GLfloat sun_mat_ambient[]   = {0.0f, 0.0f, 0.0f, 1.0f};
        GLfloat sun_mat_diffuse[]   = {0.0f, 0.0f, 0.0f, 1.0f};
        GLfloat sun_mat_specular[] = {0.0f, 0.0f, 0.0f, 1.0f};
        GLfloat sun_mat_emission[] = {0.5f, 0.0f, 0.0f, 1.0f};
        GLfloat sun_mat_shininess   = 0.0f;

        glMaterialfv(GL_FRONT, GL_AMBIENT,    sun_mat_ambient);
        glMaterialfv(GL_FRONT, GL_DIFFUSE,    sun_mat_diffuse);
        glMaterialfv(GL_FRONT, GL_SPECULAR,   sun_mat_specular);
        glMaterialfv(GL_FRONT, GL_EMISSION,   sun_mat_emission);
        glMaterialf (GL_FRONT, GL_SHININESS, sun_mat_shininess);

        glutSolidSphere(2.0, 40, 32);
    }

    // 瀹氫箟鍦扮悆鐨勬潗璐ㄥ苟缁樺埗鍦扮悆
    {
        GLfloat earth_mat_ambient[]   = {0.0f, 0.0f, 0.5f, 1.0f};
        GLfloat earth_mat_diffuse[]   = {0.0f, 0.0f, 0.5f, 1.0f};
        GLfloat earth_mat_specular[] = {0.0f, 0.0f, 1.0f, 1.0f};
        GLfloat earth_mat_emission[] = {0.0f, 0.0f, 0.0f, 1.0f};
        GLfloat earth_mat_shininess   = 30.0f;

        glMaterialfv(GL_FRONT, GL_AMBIENT,    earth_mat_ambient);
        glMaterialfv(GL_FRONT, GL_DIFFUSE,    earth_mat_diffuse);
        glMaterialfv(GL_FRONT, GL_SPECULAR,   earth_mat_specular);
        glMaterialfv(GL_FRONT, GL_EMISSION,   earth_mat_emission);
        glMaterialf (GL_FRONT, GL_SHININESS, earth_mat_shininess);

        glRotatef(mRotateY, 0.0f, -1.0f, 0.0f);
        glTranslatef(5.0f, 0.0f, 0.0f);
        glutSolidSphere(2.0, 40, 32);
    }

}
