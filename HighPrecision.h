//
// Created by PaperL on 2020/12/4.
//

#ifndef PYTHON_INTERPRETER_PAPERL_HIGHPRECISION_H
#define PYTHON_INTERPRETER_PAPERL_HIGHPRECISION_H

#include <iostream>
#include <cstdio>
#include <string>
#include <algorithm>//max/min
#include <vector>
#include <cmath>//FFT sin/cos

class FFT {
private:
    class complex {
    public:
        double re, im;

        complex(double tx = 0, double ty = 0);

        complex operator+(const complex &arg) const;

        complex operator-(const complex &arg) const;

        complex operator*(const complex &arg) const;
    };

    inline void swapC(complex &x, complex &y);

    const double pi = 3.14159265358979323846;
    std::vector<complex> a, b;
    std::vector<int> r;
    int n;

    void solveFFT(std::vector<complex> &cv, int on);

public:
    void solveMultiply(const std::vector<char> &c, const std::vector<char> &d, std::vector<int> &ans);

};

class HighPrecision {
private:

    char sign;
    std::vector<char> num;

    bool digitLess(const HighPrecision &x, const HighPrecision &y) const;

public:

    HighPrecision();

    HighPrecision(const std::string &arg);

    HighPrecision(const HighPrecision &arg, char negativeFlag = 0);


    void print() const;

    friend std::istream &operator>>(std::istream &in, HighPrecision &arg);

    friend std::ostream &operator<<(std::ostream &out, const HighPrecision &arg);


    HighPrecision &operator=(const HighPrecision &arg);


    bool operator==(const HighPrecision &arg) const;

    bool operator!=(const HighPrecision &arg) const;

    bool operator<(const HighPrecision &arg) const;

    bool operator<=(const HighPrecision &arg) const;

    bool operator>(const HighPrecision &arg) const;

    bool operator>=(const HighPrecision &arg) const;


    HighPrecision operator-() const;


    HighPrecision operator+(const HighPrecision &arg) const;

    HighPrecision operator-(const HighPrecision &arg) const;

    HighPrecision operator*(const HighPrecision &arg) const;

    HighPrecision operator/(const HighPrecision &arg) const;

    HighPrecision operator%(const HighPrecision &arg) const;

};


#endif //PYTHON_INTERPRETER_PAPERL_HIGHPRECISION_H
