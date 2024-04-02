#include <iostream>
#include <cmath>

using namespace std;

class complex {
private:
    double valid;
    double imaginary;
public:
    complex(double valid = 0.0, double imaginary = 0.0);

    void add(complex& first, complex& second);
    void sub(complex& first, complex& second);
    void mul(complex& first, complex& second);
    void div(complex& first, complex& second);

    double abs();
    double arg();

    void show() const;
};

int main() {
    system("chcp 1251>nul");

    cout << "Сложение: ";
    complex sum1(10, 5), sum2(20, 40), sum3;
    sum3.add(sum1, sum2);
    sum3.show();

    cout << "Вычитание: ";
    complex sub1(20, 10), sub2(10, 8), sub3;
    sub3.sub(sub1, sub2);
    sub3.show();

    cout << "Умножение: ";
    complex mul1(1, -1), mul2(3, 6), mul3;
    mul3.mul(mul1, mul2);
    mul3.show();

    cout << "Деление: ";
    complex div1(7, 12), div2(12, -7), div3;
    div3.div(div1, div2);
    div3.show();

    cout << "Модуль: ";
    complex abs1(-4, 3);
    cout << abs1.abs() << endl;

    cout << "Взятие аргумента: ";
    complex arg1(10, 20);
    cout << arg1.arg() << endl;

    return 0;
}

complex::complex(double valid, double imaginary) {
    this->valid = valid;
    this->imaginary = imaginary;
}

void complex::add(complex& first, complex& second) {
    valid = first.valid + second.valid;
    imaginary = first.imaginary + second.imaginary;
}

void complex::sub(complex& first, complex& second) {
    valid = first.valid - second.valid;
    imaginary = first.imaginary - second.imaginary;
}

void complex::mul(complex& first, complex& second) {
    valid = first.valid * second.valid + first.imaginary * second.imaginary * -1;
    imaginary = first.imaginary * second.valid + first.valid * second.imaginary;
}

void complex::div(complex& first, complex& second) {
    double d = second.valid * second.valid - second.imaginary * second.imaginary * -1;
    if (d == 0) {
        cout << "Деление на ноль.";
        return;
    }
    valid = (first.valid * second.valid + first.imaginary * second.imaginary) / d;
    imaginary = (first.valid * second.imaginary * -1 + second.valid * first.imaginary) / d;
}

double complex::abs() {
    return sqrt(valid * valid + imaginary * imaginary);
}

double complex::arg() {
    if (valid == 0) {
        cout << "Деление на ноль." << endl;
        exit(1);
    }
    return atan(imaginary / valid);
}

void complex::show() const {
    if (valid == 0 && imaginary == 0) cout << 0 << endl;
    else if (valid == 0 && imaginary != 0) {
        if (imaginary == 1) cout << "i" << endl;
        else cout << imaginary << "i" << endl;
    }
    else if (valid != 0 && imaginary == 0) cout << valid << endl;
    else cout << valid << " + " << imaginary << "i" << endl;
}