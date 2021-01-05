//
// Created by PaperL on 2020/12/10.
//

#ifndef PYTHON_INTERPRETER_BASICVARIABLE_H
#define PYTHON_INTERPRETER_BASICVARIABLE_H

#include <iostream>
#include <string>

#include "HighPrecision.h"

class BasicVariable {
private:

    enum ConstructorType {
        nullSetting, setNegation, setNegative
    };

    enum BasicDataType {
        pyNone, pyBoolean, pyInteger, pyFloatingPoint, pyString
    } dataType;

    bool declared;

    bool valBoolean;
    HighPrecision *valInteger;
    double *valFloatingPoint;
    std::string *valString;

    /*void strGet(const std::string &arg);

    std::string strShow();

    void print() const;*///todo get,show,print函数应该是private还是public?

public:

    BasicVariable();

    BasicVariable(const BasicVariable &arg, ConstructorType type = nullSetting);

    explicit BasicVariable(const bool &arg);

    explicit BasicVariable(const HighPrecision &arg);

    explicit BasicVariable(const double &arg);

    explicit BasicVariable(const std::string &arg);

    ~BasicVariable();


    //friend std::istream &operator>>(std::istream &in, BasicVariable &arg);

    friend std::ostream &operator<<(std::ostream &out, const BasicVariable &arg);


    BasicVariable &operator=(const BasicVariable &arg);

    char operator[](const int &index) const;


    BasicVariable operator!() const;

    BasicVariable operator&&(const BasicVariable &arg) const;

    BasicVariable operator||(const BasicVariable &arg) const;


    bool operator==(const BasicVariable &arg) const;

    bool operator!=(const BasicVariable &arg) const;

    bool operator<(const BasicVariable &arg) const;

    bool operator<=(const BasicVariable &arg) const;

    bool operator>(const BasicVariable &arg) const;

    bool operator>=(const BasicVariable &arg) const;


    BasicVariable operator-() const;


    BasicVariable operator+(const BasicVariable &arg) const;

    BasicVariable operator-(const BasicVariable &arg) const;

    BasicVariable operator*(const BasicVariable &arg) const;

    BasicVariable operator/(const BasicVariable &arg) const;

    BasicVariable operator%(const BasicVariable &arg) const;

    BasicVariable operator+=(const BasicVariable &arg) const;

    BasicVariable operator-=(const BasicVariable &arg) const;

    BasicVariable operator*=(const BasicVariable &arg) const;

    BasicVariable operator/=(const BasicVariable &arg) const;

    BasicVariable operator%=(const BasicVariable &arg) const;


    void toNone();

    void toBool();

    void toInt();

    void toDouble();

    void toStr();
};


#endif //PYTHON_INTERPRETER_BASICVARIABLE_H
