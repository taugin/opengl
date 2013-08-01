// OpenGL Class Declare

#ifndef TEXTURE_H_
#define TEXTURE_H_

#include "ModelShape.h"


class Texture: public ModelShape {
public:
    Texture();
    virtual ~Texture();

    virtual void init();
    virtual void setviewport(int width, int height);
    virtual void draw();

    GLint power_of_two(GLint n);
    GLuint loadBmpTexture(const char* filePath);
    void drawCoordinate();
    void drawWallGround();

private:
    GLuint mTexGround;
    GLuint mTexWall;
};


#endif /* TEXTURE_H_ */
