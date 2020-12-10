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

    void strGet(const std::string &arg);

    std::string strShow();

    void print() const;//todo get,show,print函数应该是private还是public?

public:
    template<class T>
    BasicVariable(BasicDataType type = pyNone, T &context = nullptr);

    BasicVariable(const BasicVariable &arg, ConstructorType type = nullSetting);

    ~BasicVariable();

    friend std::istream &operator>>(std::istream &in, HighPrecision &arg);

    friend std::ostream &operator<<(std::ostream &out, const HighPrecision &arg);


    BasicVariable &operator=(const BasicVariable &arg);


    BasicVariable &operator[](BasicVariable &arg) const;


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

};


#endif //PYTHON_INTERPRETER_BASICVARIABLE_H
