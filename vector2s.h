#ifndef VECTOR2S_H
#define VECTOR2S_H


class Vector2s
{
public:
    double X;
    double Y;

public:
    Vector2s();
    Vector2s(double x, double y);

    double Length();
    void Normalize();
    double Dot(Vector2s b);
    Vector2s Unit();

    // Operator
    bool operator == (const Vector2s& v);
    bool operator != (const Vector2s& v);
    Vector2s& operator += (const Vector2s& v);
    Vector2s& operator -= (const Vector2s& v);
    Vector2s& operator *= (const double value);
    Vector2s& operator /= (const double value);

    Vector2s operator + (const Vector2s& v2);
    Vector2s operator - (const Vector2s& v2);
    Vector2s operator * (const Vector2s& v2);
    Vector2s operator * (const double value);
    Vector2s operator / (const double value);
    Vector2s operator / (const Vector2s& v2);
    Vector2s operator - ();
};

#endif // VECTOR2S_H
