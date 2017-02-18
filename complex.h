#ifndef COMPLEX_H
#define COMPLEX_H

class Complex
{
public:
    double Real;
    double Img;

public:
    Complex();
    Complex(double _Real, double _Img);
    Complex Conj();

    // Operator
    bool operator == (const Complex& c);
    bool operator != (const Complex& c);

    Complex& operator += (const Complex& c);
    Complex& operator -= (const Complex& c);
    Complex& operator *= (const Complex& c);

    Complex operator + (const Complex& c);
    Complex operator - (const Complex& c);
    Complex operator * (const Complex& c);
    Complex operator * (const double number);
    Complex operator - ();
};

#endif // COMPLEX_H
