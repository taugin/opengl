// OpenGL Class Declare

#ifndef CIRCLE_H_
#define CIRCLE_H_
#include "ModelShape.h"


class Circle: public ModelShape {
public:
    Circle();
    virtual ~Circle();
    virtual void init();
    virtual void draw();
};

#endif /* CIRCLE_H_ */
