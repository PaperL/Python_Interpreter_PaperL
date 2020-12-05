//
// Created by PaperL on 2020/12/4.
//

#include "HighPrecision.h"

FFT FFTcmd;

FFT::complex::complex(double tx, double ty) : re(tx), im(ty) {}

FFT::complex FFT::complex::operator+(const complex &arg) const { return complex(re + arg.re, im + arg.im); }

FFT::complex FFT::complex::operator-(const complex &arg) const { return complex(re - arg.re, im - arg.im); }

FFT::complex FFT::complex::operator*(const complex &arg) const {
    return complex(re * arg.re - im * arg.im, re * arg.im + im * arg.re);
}

inline void FFT::swapC(complex &x, complex &y) {
    complex temp(x);
    x = y;
    y = temp;
}

void FFT::brc(std::vector<complex> &cv) {
    int i, j, k;
    for (i = 1, j = n / 2; i < n - 1; i++) {
        if (i < j) swapC(cv[i], cv[j]);
        k = n / 2;
        while (j >= k) {
            j -= k;
            k >>= 1;
        }
        if (j < k) j += k;
    }
}

void FFT::solveFFT(std::vector<complex> &cv, int on) {
    int i;
    brc(cv);

    for (int h = 2; h <= n; h <<= 1) {
        int tempLen = h >> 1;
        complex wn(cos(pi / tempLen), on * sin(pi / tempLen));
        for (int st = 0; st < n; st += h) {
            complex w(1, 0);
            for (i = 0; i < tempLen; ++i) {
                complex tc1 = cv[st + i];
                complex tc2 = w * cv[st + i + tempLen];
                cv[st + i] = tc1 + tc2;
                cv[st + i + tempLen] = tc1 - tc2;
                w = w * wn;
            }
        }
    }
    if (on == -1) {
        for (i = 0; i < n; ++i) cv[i].re /= n;
    }
}

void FFT::solveMultiply(const std::vector<char> &c, const std::vector<char> &d, std::vector<char> &ans) {
    int i;
    a.clear(), b.clear(), r.clear(), ans.clear();
    for (h = 0, n = 1; n < c.size() + d.size() - 1; ++h)n <<= 1;

    for (i = 0; i < c.size(); ++i)
        a.emplace_back(complex(c[i], 0));
    for (i = 0; i < d.size(); ++i)
        b.emplace_back(complex(d[i], 0));
    a.resize(n, 0), b.resize(n, 0);

    std::cout << "cp1" << std::endl;
    solveFFT(a, 1);
    solveFFT(b, 1);
    for (i = 0; i < n; ++i)a[i] = a[i] * b[i];
    std::cout << "cp2" << std::endl;
    solveFFT(a, -1);
    for (i = 0; i < n; ++i)
        ans.emplace_back(round(a[i].re));
}

bool HighPrecision::digitLess(const HighPrecision &x, const HighPrecision &y) const {
    if (x.num.size() != y.num.size())
        return (x.num.size() < y.num.size());
    for (int i = 0; i < x.num.size(); ++i) {
        if (x.num[i] != y.num[i])
            return (x.num[i] < y.num[i]);
    }
    return false;
}

HighPrecision::HighPrecision() : sign(1) { num.clear(); }

HighPrecision::HighPrecision(const std::string &arg) {
    num.clear();
    if (arg.empty())
        sign = 1;
    else {
        sign = (arg[0] == '-') ? 0 : 1;
        int tempL = arg.length() - 1 + sign;
        for (int i = 1; i <= tempL; ++i)
            num.emplace_back(arg[arg.length() - i] - 48);
    }
}

HighPrecision::HighPrecision(const HighPrecision &arg, char negativeFlag) : num(arg.num) {
    sign = (negativeFlag == 1) ? (1 - arg.sign) : arg.sign;
}

void HighPrecision::print() const {
    if (sign == 0)putchar('-');
    for (int i = num.size() - 1; i >= 0; --i)
        putchar(num[i] + 48);
}

std::istream &operator>>(std::istream &in, HighPrecision &arg) {
    std::string tempS;
    in >> tempS;
    arg = HighPrecision(tempS);
    return in;
}

std::ostream &operator<<(std::ostream &out, const HighPrecision &arg) {
    arg.print();
    return out;
}

HighPrecision &HighPrecision::operator=(const HighPrecision &arg) {
    this->sign = arg.sign;
    this->num = arg.num;
    return *this;
}

bool HighPrecision::operator==(const HighPrecision &arg) const {
    if (this->sign != arg.sign)
        return false;
    return (this->num == arg.num);
}

bool HighPrecision::operator!=(const HighPrecision &arg) const { return !((*this) == arg); }

bool HighPrecision::operator<(const HighPrecision &arg) const {
    if (this->sign < arg.sign)
        return true;
    if (this->sign > arg.sign)
        return false;

    if (this->sign == 1)
        return digitLess(*this, arg);
    else
        return !digitLess(*this, arg);
}

bool HighPrecision::operator<=(const HighPrecision &arg) const {
    if (this->sign < arg.sign)
        return true;
    if (this->sign > arg.sign)
        return false;

    if (this->num == arg.num)
        return true;

    if (this->sign == 1)
        return digitLess(*this, arg);
    else
        return !digitLess(*this, arg);
}

bool HighPrecision::operator>(const HighPrecision &arg) const { return !((*this) <= arg); }

bool HighPrecision::operator>=(const HighPrecision &arg) const { return !((*this) < arg); }

HighPrecision HighPrecision::operator-() const { return HighPrecision(*this, 1); }

HighPrecision HighPrecision::operator+(const HighPrecision &arg) const {//todo 注意空值情况
    if (this->sign == arg.sign) {
        HighPrecision tempBigInt;
        tempBigInt.sign = this->sign;
        int l1 = this->num.size(), l2 = arg.num.size();
        if (l1 > l2) {
            for (int i = 0; i < l2; ++i)
                tempBigInt.num.emplace_back(this->num[i] + arg.num[i]);
            for (int i = l2; i < l1; ++i)
                tempBigInt.num.emplace_back(this->num[i]);
            for (int i = 0; i < l1 - 1; ++i) {
                if (tempBigInt.num[i] > 9) {
                    tempBigInt.num[i] -= 10;
                    ++tempBigInt.num[i + 1];
                }
            }
            if (tempBigInt.num[l1 - 1] > 9) {
                tempBigInt.num[l1 - 1] -= 10;
                tempBigInt.num.emplace_back(1);
            }
        } else {
            for (int i = 0; i < l1; ++i)
                tempBigInt.num.emplace_back(this->num[i] + arg.num[i]);
            for (int i = l1; i < l2; ++i)
                tempBigInt.num.emplace_back(arg.num[i]);
            for (int i = 0; i < l2 - 1; ++i) {
                if (tempBigInt.num[i] > 9) {
                    tempBigInt.num[i] -= 10;
                    ++tempBigInt.num[i + 1];
                }
            }
            if (tempBigInt.num[l2 - 1] > 9) {
                tempBigInt.num[l2 - 1] -= 10;
                tempBigInt.num.emplace_back(1);
            }
        }
        return tempBigInt;
    } else {
        if (this->sign == 1)
            return ((*this) - (-arg));
        else
            return (arg - (-*this));
    }
}

HighPrecision HighPrecision::operator-(const HighPrecision &arg) const {
    if (this->sign == arg.sign) {
        if (digitLess(*this, arg))
            return (arg - (*this));
        HighPrecision tempBigInt;
        tempBigInt.sign = this->sign;
        int i;
        for (i = 0; i < arg.num.size(); ++i)
            tempBigInt.num.emplace_back(this->num[i] - arg.num[i]);
        for (i = arg.num.size(); i < this->num.size(); ++i)
            tempBigInt.num.emplace_back(this->num[i]);
        for (i = 0; i < tempBigInt.num.size() - 1; ++i) {
            if (tempBigInt.num[i] < 0) {
                tempBigInt.num[i] += 10;
                --tempBigInt.num[i + 1];
            }
        }
        while (*(tempBigInt.num.rbegin()) == 0)
            tempBigInt.num.erase(tempBigInt.num.end() - 1);
        return tempBigInt;
    } else
        return ((*this) + (-arg));
}

HighPrecision HighPrecision::operator*(const HighPrecision &arg) const {
    HighPrecision tempAns;
    FFTcmd.solveMultiply(this->num, arg.num, tempAns.num);

    for (int i = 0; i < tempAns.num.size() - 1; ++i)
        std::cout << int(tempAns.num[i]) << std::endl;

    for (int i = 0; i < tempAns.num.size() - 1; ++i) {
        if (tempAns.num[i] > 9) {
            tempAns.num[i + 1] += tempAns.num[i] / 10;
            tempAns.num[i] %= 10;
        }
        while (*tempAns.num.rbegin() > 9) {
            tempAns.num.emplace_back((*tempAns.num.rbegin()) / 10);
            *(tempAns.num.end() - 2) %= 10;
        }

    }
    return tempAns;
}