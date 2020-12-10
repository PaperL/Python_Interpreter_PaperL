//
// Created by PaperL on 2020/12/4.
//

#define warning

#include "HighPrecision.h"

FFT FFTcmd;

const HighPrecision highPrecisionZero(0);

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

void FFT::solveFFT(std::vector<complex> &cv, int on) {
    int i;
    for (i = 0; i < n; ++i) {
        if (r[i] != -1)
            swapC(cv[i], cv[r[i]]);
    }

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

void FFT::solveMultiply(const std::vector<char> &c, const std::vector<char> &d, std::vector<int> &ans) {
    int i;
    a.clear(), b.clear(), r.clear(), ans.clear();
    int t;
    std::vector<int> dig;
    for (t = 0, n = 1; n < c.size() + d.size() - 1; n <<= 1)++t;
    r.resize(n, 0);
    dig.resize(n, 0);
    for (i = 0; i < n; ++i) {
        int tempLen = 0;
        for (int j = i; j; j >>= 1)dig[tempLen++] = j & 1;
        for (int j = 0; j < t; ++j) r[i] = (r[i] << 1) | dig[j];
    }
    for (i = 0; i < n; ++i) {
        if (r[i] != -1 || r[i] >= n)
            r[r[i]] = -1;
    }
    for (i = 0; i < c.size(); ++i)
        a.emplace_back(complex(c[i], 0));
    for (i = 0; i < d.size(); ++i)
        b.emplace_back(complex(d[i], 0));
    a.resize(n, 0), b.resize(n, 0);

    solveFFT(a, 1);
    solveFFT(b, 1);
    for (i = 0; i < n; ++i)a[i] = a[i] * b[i];
    solveFFT(a, -1);

    for (i = 0; i < n; ++i)
        ans.emplace_back(round(a[i].re));
}

bool HighPrecision::digitLess(const HighPrecision &x, const HighPrecision &y) const {
    if (x.num.size() != y.num.size())
        return (x.num.size() < y.num.size());
    for (int i = x.num.size() - 1; i >= 0; --i) {
        if (x.num[i] != y.num[i])
            return (x.num[i] < y.num[i]);
    }
    return false;
}

void HighPrecision::print() const {

#ifdef warning
    if (sign != 0 && sign != 1)
        printf("WARNING: sign!=0 or 1 !\n");
    if (num.size() == 0)
        printf("WARNING: size==0!\n");
    if (sign == 0 && num.size() == 1 && num[0] == 0)
        printf("WARNING: negative zero!\n");
#endif

    if (sign == 0)putchar('-');
    for (int i = num.size() - 1; i >= 0; --i)
        putchar(num[i] + 48);
}

HighPrecision::HighPrecision(int k) : sign((k < 0) ? 0 : 1) {
    if (k == 0)
        num.emplace_back(0);
    else {
        while (k != 0) {
            num.emplace_back(k % 10);
            k /= 10;
        }
    }
}

HighPrecision::HighPrecision(const std::string &arg) {
    if (arg.empty())
        sign = 1;
    else {
        sign = (arg[0] == '-') ? 0 : 1;
        int tempL = arg.length() - 1 + sign;
        for (int i = 1; i <= tempL; ++i)
            num.emplace_back(arg[arg.length() - i] - 48);
    }
}

HighPrecision::HighPrecision(const HighPrecision &arg, char negativeFlag, int bitwiseMove) {
    if (-bitwiseMove >= int(arg.num.size())) {
        *this = highPrecisionZero;
    } else {
        sign = (negativeFlag == 1) ? (1 - arg.sign) : arg.sign;
        num.resize(bitwiseMove + int(arg.num.size()), 0);
        if (bitwiseMove < 0) {
            for (int i = 0; i < bitwiseMove + int(arg.num.size()); ++i)
                num[i] = arg.num[i - bitwiseMove];
        } else {
            for (int i = 0; i < arg.num.size(); ++i)
                num[bitwiseMove + i] = arg.num[i];
        }
    }
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
        tempBigInt.num.clear();
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
            return (-(arg - (*this)));
        if ((*this) == arg)
            return highPrecisionZero;

        HighPrecision tempBigInt;
        tempBigInt.sign = this->sign;
        tempBigInt.num.clear();
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
    if ((*this) == highPrecisionZero || arg == highPrecisionZero)
        return highPrecisionZero;

    HighPrecision ans;
    std::vector<int> tempAns;
    ans.sign = (this->sign == arg.sign) ? 1 : 0;

    FFTcmd.solveMultiply(this->num, arg.num, tempAns);

    for (int i = 0; i < tempAns.size() - 1; ++i) {
        if (tempAns[i] > 9) {
            tempAns[i + 1] += tempAns[i] / 10;
            tempAns[i] %= 10;
        }
    }
    while (*tempAns.rbegin() > 9) {
        tempAns.emplace_back((*tempAns.rbegin()) / 10);
        *(tempAns.end() - 2) %= 10;
    }
    while (*tempAns.rbegin() == 0)
        tempAns.erase(tempAns.end() - 1);

    ans.num.resize(tempAns.size(), 0);
    for (int i = 0; i < tempAns.size(); ++i)
        ans.num[i] = tempAns[i];

    return ans;
}

HighPrecision HighPrecision::operator*(int arg) const {
    if (arg == 0)
        return highPrecisionZero;
    if (arg == 1)
        return *this;
    if (arg == -1)
        return HighPrecision((*this), 1);

    HighPrecision ans;
    if (arg < 0) {
        arg = -arg;
        ans.sign = 1 - this->sign;
    } else ans.sign = this->sign;

    int t, carry = 0;
    ans.num.clear();
    for (int i = 0; i < this->num.size(); ++i) {
        t = int(this->num[i]) * arg + carry;
        carry = t / 10;
        t %= 10;
        ans.num.emplace_back(t);
    }

    while (carry) {
        t = carry % 10;
        carry /= 10;
        ans.num.emplace_back(t);
    }
    return ans;
}

HighPrecision HighPrecision::operator<<(const int &arg) const {
    return HighPrecision((*this), 0, arg);
}

HighPrecision HighPrecision::operator>>(const int arg) const {
    return HighPrecision((*this), 0, -arg);
}

HighPrecision HighPrecision::operator/(const HighPrecision &arg) const {
    if (arg == highPrecisionZero || (*this) == highPrecisionZero)
        return highPrecisionZero;
    if (digitLess((*this), arg))return highPrecisionZero;
    HighPrecision ans;
    std::vector<char> tempAns;
    ans.sign = (this->sign == arg.sign) ? 1 : 0;
    ans.num.clear();

    HighPrecision myself(*this, 1 - this->sign);
    HighPrecision tempNum;
    int i, j;
    for (i = myself.num.size() - arg.num.size(); i >= 0; --i) {
        HighPrecision tempMulti(arg, 1 - arg.sign, i);
        j = 0;
        for (j = 1; j <= 9; ++j) {
            tempNum = tempMulti * j;
            if (tempNum > myself) {
                --j;
                break;
            }
        }
        if (j == 10)j = 9;
        if (j != 0)
            myself = myself - tempMulti * j;
        tempAns.emplace_back(j);
    }

    i = 0;
    while (tempAns[i] == 0)++i;
    for (j = 0; j < tempAns.size() - i; ++j)
        ans.num.emplace_back(tempAns[tempAns.size() - 1 - j]);

    return ans;
}

HighPrecision HighPrecision::operator%(const HighPrecision &arg) const {
    if (arg == highPrecisionZero || (*this) == highPrecisionZero)
        return highPrecisionZero;
    if (digitLess((*this), arg))return (*this);

    HighPrecision myself(*this, 1 - this->sign);
    HighPrecision tempNum;
    int i, j;
    for (i = myself.num.size() - arg.num.size(); i >= 0; --i) {
        HighPrecision tempMulti(arg, 1 - arg.sign, i);
        j = 0;
        for (j = 1; j <= 9; ++j) {
            tempNum = tempMulti * j;
            if (tempNum > myself) {
                --j;
                break;
            }
        }
        if (j == 10)j = 9;
        if (j != 0)
            myself = myself - tempMulti * j;
    }
    if (this->sign == 1 || myself == highPrecisionZero)
        return myself;
    else return (-myself);
}