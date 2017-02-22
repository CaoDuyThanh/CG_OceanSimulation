#include "complex.h"

Complex::Complex() {
    this->Real = 0;
    this->Img = 0;
}

Complex::Complex(double _Real, double _Img)
{
    this->Real = _Real;
    this->Img = _Img;
}

Complex Complex::Conj() {
    return Complex(this->Real, this->Img);
}

// Operator
void Complex::operator = (const Complex& c) {
    this->Real = c.Real;
    this->Img = c.Img;
}

bool Complex::operator == (const Complex& c){
    return (this->Real == c.Real && this->Img == c.Img);
}

bool Complex::operator != (const Complex& c){
    return (this->Real != c.Real || this->Img != c.Img);
}

Complex& Complex::operator += (const Complex& c){
    this->Real += c.Real;
    this->Img += c.Img;
    return *this;
}

Complex& Complex::operator -= (const Complex& c){
    this->Real -= c.Real;
    this->Img -= c.Img;
    return *this;
}

Complex& Complex::operator *= (const Complex& c){
    double realTemp = this->Real;
    double imgTemp = this->Img;
    this->Real = realTemp * c.Real - imgTemp * c.Img;
    this->Img = realTemp * c.Img + imgTemp * c.Real;
    return *this;
}

Complex Complex::operator + (const Complex& c){
    return Complex(this->Real + c.Real, this->Img + c.Img);
}

Complex Complex::operator - (const Complex& c){
    return Complex(this->Real - c.Real, this->Img - c.Img);
}

Complex Complex::operator * (const Complex& c){
    return Complex(this->Real * c.Real - this->Img * c.Img,
                   this->Real * c.Img + this->Img * c.Real);
}

Complex Complex::operator * (const double number){
    return Complex(this->Real * number, this->Img * number);
}

Complex Complex::operator - (){
    this->Real = -this->Real;
    this->Img = -this->Img;
    return *this;
}
