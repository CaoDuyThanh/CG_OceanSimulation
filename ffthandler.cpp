#include "ffthandler.h"
#include <iostream>
using namespace std;
#define PI 3.1415

FFTHandler::FFTHandler(int _size) {
    this->size = _size;
    this->matrix = new Complex[this->size * this->size];
    this->matrixD = new Complex[this->size * this->size];
    this->temp = new Complex[this->size * this->size];
    this->result = new Complex[this->size * this->size];
}

FFTHandler::~FFTHandler() {
    delete this->matrix;
    delete this->matrixD;
    delete this->temp;
    delete this->result;
}

Complex FFTHandler::T(int _x, int _N) {
    double real = cos(2.0 * PI * _x / _N);
    double imag = sin(2.0 * PI * _x / _N);
    return Complex(real, imag);
}

void FFTHandler::FFT1D(Complex* _input, Complex* _output, int _N) {
    if (_N == 1) {
        *_output = _input->Conj();
    } else {
        Complex* inputEven = new Complex[_N / 2];
        Complex* inputOdd = new Complex[_N / 2];
        for (int i = 0; i < _N / 2; i++) {
            inputEven[i] = _input[i * 2];
            inputOdd[i] = _input[i * 2 + 1];
        }

        Complex* outputEven = new Complex[_N / 2];
        Complex* outputOdd = new Complex[_N / 2];
        this->FFT1D(inputEven, outputEven, _N / 2);
        this->FFT1D(inputOdd, outputOdd, _N / 2);

        for (int i = 0; i < _N / 2; i++) {
            _output[i] = outputEven[i] - outputOdd[i] * this->T(i, _N);
            _output[i + _N / 2] = outputEven[i] - outputOdd[i];
        }

        delete inputEven;
        delete inputOdd;
        delete outputEven;
        delete outputOdd;
    }
}

void FFTHandler::calculateFFT() {
    // Calculate fft row first
    Complex* dataRow = new Complex[this->size];
    Complex* resultRow = new Complex[this->size];
    int index;
    for (int row = 0; row < this->size; row++) {
        for (int col = 0; col < this->size; col++) {
            index = row * this->size + col;
            dataRow[col] = this->matrix[index];
        }
//        cout << "Row   ---   " << row ;
//        for (int k = 0; k < this->size; k++) {
//            cout << "("<< dataRow[k].Real << "," << dataRow[k].Img << ")" << " ";
//        }
//        cout << "\n";
        this->FFT1D(dataRow, resultRow, this->size);
        for (int col = 0; col < this->size; col++) {
            index = row * this->size + col;
            this->temp[index] = resultRow[col];
        }
//        cout << "Row   ---   " << row ;
//        for (int k = 0; k < this->size; k++) {
//            cout << "("<< resultRow[k].Real << "," << resultRow[k].Img << ")" << " ";
//        }
//        cout << "\n";
    }

    for (int col = 0; col < this->size; col++) {
        for (int row = 0; row < this->size; row++) {
            index = row * this->size + col;
            dataRow[row] = this->temp[index];
        }
        this->FFT1D(dataRow, resultRow, this->size);
        for (int row = 0; row < this->size; row++) {
            index = row * this->size + col;
            this->result[index] = resultRow[row];
        }
    }

    delete dataRow;
    delete resultRow;
}


