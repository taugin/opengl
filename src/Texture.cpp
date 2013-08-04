// OpenGL Class Implement
#include <stdio.h>
#include <stdlib.h>
#include "Texture.h"

#define BMP_HEADER_LENGTH 54
#define WALL_FILE_PATH "res/textures/wall.bmp"
#define GROUND_FILE_PATH "res/textures/ground.bmp"

Texture::Texture()
        : mTexGround(0)
        , mTexWall(0) {

}
Texture::~Texture() {

}

void Texture::init() {
    glEnable(GL_DEPTH_TEST);
    mTexGround = loadBmpTexture(GROUND_FILE_PATH);
    DEBUG("mTexGround = %d\n", mTexGround);
    mTexWall = loadBmpTexture(WALL_FILE_PATH);
    DEBUG("mTexWall = %d\n", mTexWall);
}
void Texture::setviewport(int width, int height) {
    ModelShape::setviewport(width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(mfovy, 1, 1, 21);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(1, 5, 5, 0, 0, 0, 0, 0, 1);
    //gluLookAt(0, 0, 10, 0, 0, 0, 0, 1, 0);
}

void Texture::drawCoordinate() {
    GLfloat lineXWidth = mModelState == STATE_ROTATE_X || mModelState == STATE_SCALE ? 10 : 1;
    GLfloat lineYWidth = mModelState == STATE_ROTATE_Y || mModelState == STATE_SCALE ? 10 : 1;
    GLfloat lineZWidth = mModelState == STATE_ROTATE_Z || mModelState == STATE_SCALE ? 10 : 1;

    glLineWidth(lineXWidth);
    glBegin(GL_LINES);
        glColor3f(1, 0, 0);
        glVertex3f(0, 0, 0);
        glVertex3f(5, 0, 0);
    glEnd();

    glLineWidth(lineYWidth);
    glBegin(GL_LINES);
        glColor3f(0, 1, 0);
        glVertex3f(0, 0, 0);
        glVertex3f(0, 5, 0);
    glEnd();

    glLineWidth(lineZWidth);
    glBegin(GL_LINES);
        glColor3f(0, 0, 1);
        glVertex3f(0, 0, 0);
        glVertex3f(0, 0, 10);
    glEnd();
    glLineWidth(1);
}
void Texture::draw() {
    DEBUG("Texture::draw\n");
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glPushMatrix();
    DEBUG("mRotateX = %f, mRotateY = %f, mRotateZ = %f\n", mRotateX, mRotateY, mRotateZ);
    glRotatef(mRotateX, 1, 0, 0);
    glRotatef(mRotateY, 0, 1, 0);
    glRotatef(mRotateZ, 0, 0, 1);
    drawWallGround();
    glPopMatrix();
    drawCoordinate();
    glutSwapBuffers();
}


int Texture::power_of_two(GLint n) {
    if( n <= 0 )
        return 0;
    return (n & (n-1)) == 0;
}
void Texture::drawWallGround() {
    // Ground
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, mTexGround);
    //glutSolidSphere(2,80,80);
    glBegin(GL_QUADS);
        glTexCoord2f(0.0f, 0.0f);
        glVertex3f(-8.0f, -8.0f, 0.0f);
        glTexCoord2f(0.0f, 5.0f);
        glVertex3f(-8.0f, 8.0f, 0.0f);
        glTexCoord2f(5.0f, 5.0f);
        glVertex3f(8.0f, 8.0f, 0.0f);
        glTexCoord2f(5.0f, 0.0f);
        glVertex3f(8.0f, -8.0f, 0.0f);
    glEnd();
    // wall
    glBindTexture(GL_TEXTURE_2D, mTexWall);
    glBegin(GL_QUADS);
        glTexCoord2f(0.0f, 0.0f);
        glVertex3f(-6.0f, -3.0f, 0.0f);
        glTexCoord2f(0.0f, 1.0f);
        glVertex3f(-6.0f, -3.0f, 1.5f);
        glTexCoord2f(5.0f, 1.0f);
        glVertex3f(6.0f, -3.0f, 1.5f);
        glTexCoord2f(5.0f, 0.0f);
        glVertex3f(6.0f, -3.0f, 0.0f);
    glEnd();


    glRotatef(-90, 0, 0, 1);
    glBegin(GL_QUADS);
        glTexCoord2f(0.0f, 0.0f);
        glVertex3f(-6.0f, -3.0f, 0.0f);
        glTexCoord2f(0.0f, 1.0f);
        glVertex3f(-6.0f, -3.0f, 1.5f);
        glTexCoord2f(5.0f, 1.0f);
        glVertex3f(6.0f, -3.0f, 1.5f);
        glTexCoord2f(5.0f, 0.0f);
        glVertex3f(6.0f, -3.0f, 0.0f);
    glEnd();
    glDisable(GL_TEXTURE_2D);
}
GLuint Texture::loadBmpTexture(const char* filePath) {
    GLint width = 0;
    GLint height = 0;
    GLint total_bytes = 0;
    GLubyte* pixels = NULL;
    GLuint last_texture_ID = 0;
    GLuint texture_ID = 0;

    if (filePath == NULL) {
        DEBUG("filePath == NULL\n");
        return 0;
    }

    FILE* pFile = fopen(filePath, "rb");
    if (pFile == NULL) {
        DEBUG("pFile == NULL\n");
        return 0;
    }

    fseek(pFile, 0x0012, SEEK_SET);
    if (fread(&width, 4, 1, pFile) <=0) {
        DEBUG("read width error\n");
        return 0;
    }
    if (fread(&height, 4, 1, pFile) <= 0) {
        DEBUG("read height error\n");
        return 0;
    }
    fseek(pFile, BMP_HEADER_LENGTH, SEEK_SET);

    //Calculate the bytes of whole line, and the total bytes
    GLint line_bytes = width * 3;
    DEBUG("line_bytes = %d\n", line_bytes);
    /*
    while (line_bytes & (line_bytes - 1) != 0) {
        line_bytes ++;
    }
    */
    while (line_bytes %4 != 0) {
        line_bytes ++;
    }
    DEBUG("line_bytes alignment = %d\n", line_bytes);
    total_bytes = total_bytes + line_bytes * height;
    DEBUG("total_bytes = %d\n", total_bytes);

    // Allocate the memory
    pixels = (GLubyte *)malloc(total_bytes);
    if (pixels == NULL) {
        DEBUG("pixels == NULL\n");
        fclose(pFile);
        return 0;
    }

    // Read pixel data
    if (fread(pixels, total_bytes, 1, pFile) <= 0) {
        DEBUG("fread bytes <=0 \n");
        free(pixels);
        fclose(pFile);
        return 0;
    }

    // adjust the real image to the proper
    GLint max;
    glGetIntegerv(GL_MAX_TEXTURE_SIZE, &max);

    if (!power_of_two(width) || !power_of_two(height) || width > max || height > max) {
        const GLint new_width = 256;
        const GLint new_height = 256;
        GLint new_line_bytes = 0;
        GLint new_total_bytes = 0;
        GLubyte* new_pixels = NULL;

        new_line_bytes = new_width * 3;
        /*
        while (new_line_bytes & (new_line_bytes - 1) != 0) {
            new_line_bytes ++;
        }
        */
        while (new_line_bytes %4 != 0) {
            line_bytes ++;
        }
        new_total_bytes = new_line_bytes * new_height;

        //
        new_pixels = (GLubyte*) malloc(new_total_bytes);
        if (new_pixels == 0) {
            DEBUG("new_pixels == NULL\n");
            free(pixels);
            fclose(pFile);
            return 0;
        }

        gluScaleImage(GL_RGB
                , width
                , height
                , GL_UNSIGNED_BYTE
                , (void*)pixels
                , new_width
                , new_height
                , GL_UNSIGNED_BYTE
                , (void*)new_pixels);

        // free the old memory
        free(pixels);
        pixels = new_pixels;
        width = new_width;
        height = new_height;

    }
    // Generate the texture_id
    glGenTextures(1, &texture_ID);
    if (texture_ID == 0) {
        free(pixels);
        fclose(pFile);
        return 0;
    }
    // set the texture parameter

    glGetIntegerv(GL_TEXTURE_BINDING_2D, (GLint*)&last_texture_ID);
    glBindTexture(GL_TEXTURE_2D, texture_ID);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pixels);
    glBindTexture(GL_TEXTURE_2D, last_texture_ID);

    free(pixels);
    return texture_ID;
}
