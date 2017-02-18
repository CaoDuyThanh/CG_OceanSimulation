#include "complexvectornormal.h"

ComplexVectorNormal::ComplexVectorNormal() {
    this->h = Complex();
    this->D = Vector2s();
    this->n = Vector3s();
}

ComplexVectorNormal::ComplexVectorNormal(Complex _h, Vector2s _D, Vector3s _n)
{
    this->h = _h;
    this->D = _D;
    this->n = _n;
}
