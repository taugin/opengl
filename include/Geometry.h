// OpenGL Class Declare

#ifndef GEOMETRY_H_
#define GEOMETRY_H_

#include "ModelShape.h"


class Geometry: public ModelShape {
public:
    Geometry();
    virtual ~Geometry();
    virtual void draw();

    void drawLines();
    void drawPoints();
    void drawLineStipple();
    void reversal();
    void globeModel();
    void lightGlobalModel();
};

#endif /* GEOMETRY_H_ */
