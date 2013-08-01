// OpenGL Class Declare

#ifndef CAR_H_
#define CAR_H_

#include "ModelShape.h"

class Car: public ModelShape {
public:
    Car();
    virtual ~Car();

    virtual void init();
    virtual void setviewport(int width, int height);
    virtual void draw();

    void drawCar();
    void drawCoordinate();
    void drawWheel();
    void drawCircle();
};

#endif /* CAR_H_ */
