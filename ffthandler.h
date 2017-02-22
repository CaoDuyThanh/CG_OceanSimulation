#ifndef FFTHANDLER_H
#define FFTHANDLER_H
#include <math.h>
#include "complex.h"

class FFTHandler
{
protected:
    int size;
    Complex* matrix;
    Complex* matrixD;
    Complex* temp;
    Complex* result;

public:
    FFTHandler(int);
    ~FFTHandler();

protected:
    Complex T(int, int);
    void FFT1D(Complex*, Complex*, int);
    void calculateFFT();

};

#endif // FFTHANDLER_H
