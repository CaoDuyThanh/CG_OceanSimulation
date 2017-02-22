#ifndef OCEANHANDLER_H
#define OCEANHANDLER_H
#include <math.h>
#include <random>
#include <GL/gl.h>
#include "complex.h"
#include "vector2s.h"
#include "vector3s.h"
#include "complexvectornormal.h"
#include "vertexocean.h"
#include "ffthandler.h"

using namespace std;

class OceanHandler: FFTHandler
{
public:
    int N;
    int Nplus1;
    double Length;
    double G;
    double A;
    Vector2s W;
    VertexOcean* Vertices;

public:
    OceanHandler(int _N, double _A, double _Length, double _G, Vector2s _W);

    float dispersion(int _n_prime, int _m_prime);
    float phillips(int _n_prime, int _m_prime);
    Complex hTile_0(int _n_prime, int _m_prime);
    Complex hTile(float _t, int _n_prime, int _m_prime);
    ComplexVectorNormal h_D_n(Vector2s x, float t);
    void evaluateWaves(float _t);
    void evaluateWavesFFT(float _t);
    void Render();

    ~OceanHandler();
};

#endif // OCEANHANDLER_H
