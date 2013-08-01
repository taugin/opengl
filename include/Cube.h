// OpenGL Class Declare

#ifndef CUBE_H_
#define CUBE_H_

#include "ModelShape.h"


class Cube: public ModelShape {
public:
    Cube();
    virtual ~Cube();
    virtual void draw();
};

#endif /* CUBE_H_ */
