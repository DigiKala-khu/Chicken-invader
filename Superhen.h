#ifndef SUPERHEN_H
#define SUPERHEN_H
#include "Chicken.h"

class Superhen : public Chicken
{
public:
    Superhen(int row);


public slots:
    virtual void motionWings();
    virtual void moveDown();
};

#endif // SUPERHEN_H
