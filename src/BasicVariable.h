//
// Created by PaperL on 2020/12/10.
//

#ifndef PYTHON_INTERPRETER_BASICVARIABLE_H
#define PYTHON_INTERPRETER_BASICVARIABLE_H

#include <iostream>
#include <string>
#include <sstream>//double to string

#include "HighPrecision.h"
#include "robust.h"

class BasicVariable {
public:
    enum ConstructorType {
        setDefault, setNone, setNegation, setPositive, setNegative, setName
    };

    enum BasicDataType {
        pyNull, pyName, pyNone, pyBoolean, pyInteger, pyFloatingPoint, pyString
    };

private:
    BasicDataType dataType;

    std::string *name;

    bool valBoolean;
    HighPrecision *valInteger;
    double *valFloatingPoint;
    std::string *valString;

    /*void strGet(const std::string &arg);

    std::string strShow();

    void print() const;*/

public:

    BasicVariable(ConstructorType type = setDefault);

    BasicVariable(const BasicVariable &arg, ConstructorType type = setDefault);

    explicit BasicVariable(const bool &arg);

    explicit BasicVariable(const HighPrecision &arg);

    explicit BasicVariable(const double &arg);

    explicit BasicVariable(const std::string &arg, ConstructorType type = setDefault);

    ~BasicVariable();


    BasicDataType getType() const;

    std::string &getName() const;

    bool getBool() const;

    HighPrecision &getInt() const;

    double &getFloat() const;

    std::string &getString() const;


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


    BasicVariable operator+() const;

    BasicVariable operator-() const;


    BasicVariable operator+(const BasicVariable &arg) const;

    BasicVariable operator-(const BasicVariable &arg) const;

    BasicVariable operator*(const BasicVariable &arg) const;

    BasicVariable operator/(const BasicVariable &arg) const;

    BasicVariable operator%(const BasicVariable &arg) const;

    BasicVariable operator+=(const BasicVariable &arg);

    BasicVariable operator-=(const BasicVariable &arg);

    BasicVariable operator*=(const BasicVariable &arg);

    BasicVariable operator/=(const BasicVariable &arg);

    BasicVariable operator%=(const BasicVariable &arg);


    BasicVariable &toNone();

    BasicVariable &toBool();

    BasicVariable &toInt();

    BasicVariable &toFloat();

    BasicVariable &toStr();


    bool isNull() const;
};


#endif //PYTHON_INTERPRETER_BASICVARIABLE_H
