// OpenGL Class Declare

#ifndef SINE_H_
#define SINE_H_
#include "ModelShape.h"


class Sine: public ModelShape {
public:
    Sine();
    virtual ~Sine();
    virtual void draw();
};

#endif /* SINE_H_ */
