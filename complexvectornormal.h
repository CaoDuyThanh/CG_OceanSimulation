#ifndef COMPLEXVECTORNORMAL_H
#define COMPLEXVECTORNORMAL_H
#include "complex.h"
#include "vector2s.h"
#include "vector3s.h"

class ComplexVectorNormal
{
public:
    Complex h;
    Vector2s D;
    Vector3s n;

public:
    ComplexVectorNormal();
    ComplexVectorNormal(Complex, Vector2s, Vector3s);
};

#endif // COMPLEXVECTORNORMAL_H
