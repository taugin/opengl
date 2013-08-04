// OpenGL Class Declare

#ifndef RECT_H_
#define RECT_H_
#include "ModelShape.h"


class Rect: public ModelShape {
public:
    Rect();
    virtual ~Rect();
    virtual void draw();
};

#endif /* RECT_H_ */
