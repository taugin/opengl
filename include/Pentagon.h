// OpenGL Class Declare

#ifndef PENTAGON_H_
#define PENTAGON_H_
#include "ModelShape.h"


class Pentagon: public ModelShape {
public:
    Pentagon();
    virtual ~Pentagon();

    virtual void draw();
};

#endif /* PENTAGON_H_ */
