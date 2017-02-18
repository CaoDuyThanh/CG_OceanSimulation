#include "oceanhandler.h"
#define PI 3.1415


OceanHandler::OceanHandler(int _N,
                           double _A,
                           double _Length,
                           double _G,
                           Vector2s _W)
{
    this->N = _N;
    this->A = _A;
    this->Nplus1 = _N + 1;
    this->G = _G;
    this->Length = _Length;
    this->W = _W;

    this->Vertices = new VertexOcean[this->Nplus1 * this->Nplus1];
    int index;
    Complex htile0, htile0mk_conj;
    for (int m_prime = 0; m_prime < this->Nplus1; m_prime++) {
        for (int n_prime = 0; n_prime < this->Nplus1; n_prime++) {
            index = m_prime * this->Nplus1 + n_prime;

            htile0        = hTile_0(n_prime, m_prime);
            htile0mk_conj = hTile_0(n_prime, m_prime).Conj();

            this->Vertices[index].A = htile0.Real;
            this->Vertices[index].B = htile0.Img;
            this->Vertices[index]._A = htile0mk_conj.Real;
            this->Vertices[index]._B = htile0mk_conj.Img;

            this->Vertices[index].Ox = this->Vertices[index].X = (n_prime - this->N / 2.0f);
            this->Vertices[index].Oy = this->Vertices[index].Y = 0.0f;
            this->Vertices[index].Oz = this->Vertices[index].Z = (m_prime - this->N / 2.0f);

            this->Vertices[index].Nx = 0.0f;
            this->Vertices[index].Ny = 1.0f;
            this->Vertices[index].Nz = 0.0f;
        }
    }
}

float uniformRandomVariable() {
    return (float)rand() / RAND_MAX;
}

Complex gaussianRandomVariable() {
    float x1, x2, w;
    do {
        x1 = 2.f * uniformRandomVariable() - 1.f;
        x2 = 2.f * uniformRandomVariable() - 1.f;
        w = x1 * x1 + x2 * x2;
    } while ( w >= 1.f );
    w = sqrt((-2.f * log(w)) / w);
    return Complex(x1 * w, x2 * w);
}

float OceanHandler::dispersion(int _n_prime, int _m_prime) {    // What is this function
    float w_0 = 2.0f * PI / 200.0f;
    float kx = PI * ( 2 * _n_prime - this->N) / this->Length;
    float kz = PI * ( 2 * _m_prime - this->N) / this->Length;
    return floor(sqrt(this->G * sqrt(kx *kx + kz * kz)) / w_0) * w_0;
}

float OceanHandler::phillips(int _n_prime, int _m_prime) {
    Vector2s k(PI * (2 * _n_prime - this->N) / this->Length,
               PI * (2 * _m_prime - this->N) / this->Length);
    float k_length = k.Length();
    if (k_length < 0.000001) return 0.0;

    float k_length2 = k_length * k_length;
    float k_length4 = k_length2 * k_length2;

    float k_dot_w = k.Unit().Dot(this->W.Unit());
    float k_dot_w2 = k_dot_w * k_dot_w;

    float w_length = this->W.Length();
    float L = w_length * w_length / this->G;
    float L2 = L * L;

    float damping = 0.001;
    float l2 = L2 * damping * damping;

    return A * exp(-1.0f / (k_length2 * L2)) / k_length4 * k_dot_w2 * exp(-k_length2 * l2);
}

Complex OceanHandler::hTile_0(int _n_prime, int _m_prime) {
    Complex r = gaussianRandomVariable();
    return r * sqrt(phillips(_n_prime, _m_prime) / 2.0f);
}

Complex OceanHandler::hTile(float _t, int _n_prime, int _m_prime) {
    int index = _m_prime * this->Nplus1 + _n_prime;

    Complex htile0(this->Vertices[index].A, this->Vertices[index].A);       // What is a, b
    Complex htile0mkconj(this->Vertices[index]._A, this->Vertices[index]._B); // What is _a, _b

    float omegat = dispersion(_n_prime, _m_prime) * _t;

    float cos_ = cos(omegat);
    float sin_ = sin(omegat);

    Complex res = htile0 * cos_ + htile0mkconj * sin_;

    return res;
}

ComplexVectorNormal OceanHandler::h_D_n(Vector2s x, float t) {
    Complex h(0.0f, 0.0f);
    Vector2s D(0.0f, 0.0f);
    Vector3s n(0.0f, 0.0f, 0.0f);

    Complex c, res, htile_c;
    Vector2s k;
    float kx, kz, k_length, k_dot_x;

    for (int m_prime = 0; m_prime < this->Nplus1; m_prime++) {
        kz = 2.0f * PI * (m_prime - this->N / 2.0f) / this->Length;
        for (int n_prime = 0; n_prime < this->Nplus1; n_prime++) {
            kx = 2.0 * PI * (n_prime - this->N / 2.0f) / this->Length;
            k = Vector2s(kx, kz);

            k_length = k.Length();
            k_dot_x = k.Dot(x);

            c = Complex(cos(k_dot_x), sin(k_dot_x));
            htile_c = hTile(t, n_prime, m_prime) * c;

            h = h + htile_c;

            n = n + Vector3s(-kx * htile_c.Img, 0.0f, -kz + htile_c.Img);

            if (k_length < 0.000001) continue;
            D = D + Vector2s(kx / k_length * htile_c.Img, kz / k_length * htile_c.Img);
        }
    }

    n = (Vector3s(0.0, 1.0f, 0.0f) - n).Unit();
    ComplexVectorNormal cvn(h, D, n);

    return cvn;
}

void OceanHandler::evaluateWaves(float _t) {
    float lambda = -1.0;
    int index;
    Vector2s x;
    Vector2s d;
    ComplexVectorNormal h_d_n;

    for (int m_prime = 0; m_prime < Nplus1; m_prime++) {
        for (int n_prime = 0; n_prime < Nplus1; n_prime++) {
            index = m_prime * this->Nplus1 + n_prime;

            x = Vector2s(this->Vertices[index].X, this->Vertices[index].Z);

            h_d_n = h_D_n(x, _t);

            this->Vertices[index].Y = h_d_n.h.Real;

            this->Vertices[index].X = this->Vertices[index].Ox + lambda * h_d_n.D.X;
            this->Vertices[index].Z = this->Vertices[index].Oz + lambda * h_d_n.D.Y;

            this->Vertices[index].Nx = h_d_n.n.X;
            this->Vertices[index].Ny = h_d_n.n.Y;
            this->Vertices[index].Nz = h_d_n.n.Z;
        }
    }
}

void OceanHandler::Render() {
    glBegin(GL_TRIANGLES);
    for (int m_prime = 0; m_prime < N; m_prime++) {
        for (int n_prime = 0; n_prime < N; n_prime++) {
            VertexOcean A = this->Vertices[m_prime * this->Nplus1 + n_prime];
            VertexOcean B = this->Vertices[m_prime * this->Nplus1 + n_prime + 1];
            VertexOcean C = this->Vertices[(m_prime + 1) * (this->Nplus1) + n_prime];
            VertexOcean D = this->Vertices[(m_prime + 1) * (this->Nplus1) + n_prime + 1];
            glVertex3d(A.X, A.Y, A.Z);
            glVertex3d(C.X, C.Y, C.Z);
            glVertex3d(B.X, B.Y, B.Z);

            glVertex3d(B.X, B.Y, B.Z);
            glVertex3d(C.X, C.Y, C.Z);
            glVertex3d(D.X, D.Y, D.Z);
        }
    }
    glEnd();
}

OceanHandler::~OceanHandler(){
}
