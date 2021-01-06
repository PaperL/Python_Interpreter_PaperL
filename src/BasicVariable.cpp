//
// Created by PaperL on 2020/12/10.
//

#include "BasicVariable.h"

/*void BasicVariable::strGet(const std::string &arg) {

}

std::string BasicVariable::strShow() {

}

void BasicVariable::print() const {

}*/

BasicVariable::BasicVariable(ConstructorType type) : dataType(pyNull),
                                                     name(nullptr),
                                                     valBoolean(false),
                                                     valInteger(nullptr),
                                                     valFloatingPoint(nullptr),
                                                     valString(nullptr) {
    if (type == setNone)
        dataType = pyNone;
}

BasicVariable::BasicVariable(const BasicVariable &arg, ConstructorType type) : dataType(arg.dataType),
                                                                               name(arg.name),
                                                                               valBoolean(arg.valBoolean),
                                                                               valInteger(arg.valInteger),
                                                                               valFloatingPoint(arg.valFloatingPoint),
                                                                               valString(arg.valString) {
    if (type == setNegation) {
        if (dataType == pyBoolean)
            valBoolean = !valBoolean;
    } else if (type == setNegative) {
        if (dataType == pyInteger && valInteger != nullptr)//nullptr判断冗余
            *valInteger = -(*valInteger);
        else if (dataType == pyFloatingPoint && valFloatingPoint != nullptr)
            *valFloatingPoint = -(*valFloatingPoint);
    }
}

BasicVariable::BasicVariable(const bool &arg) : BasicVariable() {
    dataType = pyBoolean;
    valBoolean = arg;
}

BasicVariable::BasicVariable(const HighPrecision &arg) : BasicVariable() {
    dataType = pyInteger;
    valInteger = new HighPrecision(arg);
}

BasicVariable::BasicVariable(const double &arg) : BasicVariable() {
    dataType = pyFloatingPoint;
    valFloatingPoint = new double(arg);
}

BasicVariable::BasicVariable(const std::string &arg, ConstructorType type) : BasicVariable() {
    if (type == setDefault) {
        dataType = pyString;
        valString = new std::string(arg);
    } else if (type == setName) {
        dataType = pyName;
        name = new std::string(arg);
    }
}

BasicVariable::~BasicVariable() {
    if (dataType == pyName)
        delete name;
    else if (dataType == pyInteger)
        delete valInteger;
    else if (dataType == pyFloatingPoint)
        delete valFloatingPoint;
    else if (dataType == pyString)
        delete valString;
}

BasicVariable::BasicDataType BasicVariable::getType() { return dataType; }

std::string &BasicVariable::getName() { return *name; }

/*std::istream &operator>>(std::istream &in, BasicVariable &arg) {

    return in;
}*/

std::ostream &operator<<(std::ostream &out, const BasicVariable &arg) {
    if (arg.dataType == BasicVariable::pyNull)
        throw pyException("Output Null Variable");
    else if (arg.dataType == BasicVariable::pyName)
        throw pyException("Output Variable's Name");
    else if (arg.dataType == BasicVariable::pyNone)
        std::cout << "None";
    else if (arg.dataType == BasicVariable::pyBoolean)
        std::cout << (arg.valBoolean ? "True" : "False");
    else if (arg.dataType == BasicVariable::pyInteger)
        std::cout << *(arg.valInteger);
    else if (arg.dataType == BasicVariable::pyFloatingPoint)
        std::cout << *(arg.valFloatingPoint);
    else if (arg.dataType == BasicVariable::pyString)
        std::cout << *(arg.valString);
    return out;
}

BasicVariable &BasicVariable::operator=(const BasicVariable &arg) {
    if (this == &arg)return *this;
    if (dataType == pyName)
        delete name;
    else if (dataType == pyInteger)
        delete valInteger;
    else if (dataType == pyFloatingPoint)
        delete valFloatingPoint;
    else if (dataType == pyString)
        delete valString;
    dataType = arg.dataType;
    if (dataType == pyName)
        name = new std::string(*arg.name);
    else if (dataType == pyBoolean)
        valBoolean = arg.valBoolean;
    else if (dataType == pyInteger)
        valInteger = new HighPrecision(*arg.valInteger);//todo 构造函数使用方式是否正确？
    else if (dataType == pyFloatingPoint)
        valFloatingPoint = new double(*arg.valFloatingPoint);
    else if (dataType == pyString)
        valString = new std::string(*arg.valString);

    return *this;
}

char BasicVariable::operator[](const int &index) const {
    if (dataType == pyString && index < valString->length())
        return (*valString)[index];
    else throw pyException("Use Not-string Variable's operator[]");
}

BasicVariable BasicVariable::operator!() const {
    if (dataType == pyBoolean)
        return BasicVariable(*this, setNegation);
    else {
        throw pyException("Warning: Use Not-boolean Variable's operator!");
        /*if(dataType==pyInteger)
            return BasicVariable(pyBoolean,!(*valInteger).isZero());
        else if(dataType == pyFloatingPoint)
            return BasicVariable(pyBoolean,(*valFloatingPoint)*/
    }
}

BasicVariable BasicVariable::operator&&(const BasicVariable &arg) const {
    //if (dataType != pyBoolean)
}

BasicVariable BasicVariable::operator||(const BasicVariable &arg) const {

}

bool BasicVariable::operator==(const BasicVariable &arg) const {

}

bool BasicVariable::operator!=(const BasicVariable &arg) const {

}

bool BasicVariable::operator<(const BasicVariable &arg) const {

}

bool BasicVariable::operator<=(const BasicVariable &arg) const {

}

bool BasicVariable::operator>(const BasicVariable &arg) const {

}

bool BasicVariable::operator>=(const BasicVariable &arg) const {

}

BasicVariable BasicVariable::operator-() const {

}

BasicVariable BasicVariable::operator+(const BasicVariable &arg) const {
    if (dataType == arg.dataType) {
        if (dataType == pyInteger)
            return BasicVariable(*valInteger + *(arg.valInteger));
        else if (dataType == pyInteger)
            return BasicVariable(*valFloatingPoint + *(arg.valFloatingPoint));
        else if (dataType == pyString)
            return BasicVariable(*valString + *(arg.valString));
    } else throw pyException("Warning: try to plus two basicVariable of different types");
    throw pyException("Warning: try to plus two basicVariable of wrong type");
}

BasicVariable BasicVariable::operator-(const BasicVariable &arg) const {

}

BasicVariable BasicVariable::operator*(const BasicVariable &arg) const {

}

BasicVariable BasicVariable::operator/(const BasicVariable &arg) const {

}

BasicVariable BasicVariable::operator%(const BasicVariable &arg) const {

}

BasicVariable BasicVariable::operator+=(const BasicVariable &arg) const { return (*this) + arg; }

BasicVariable BasicVariable::operator-=(const BasicVariable &arg) const { return (*this) - arg; }

BasicVariable BasicVariable::operator*=(const BasicVariable &arg) const { return (*this) * arg; }

BasicVariable BasicVariable::operator/=(const BasicVariable &arg) const { return (*this) / arg; }

BasicVariable BasicVariable::operator%=(const BasicVariable &arg) const { return (*this) % arg; }

void BasicVariable::toNone() {
    if (dataType == pyName)
        delete name;
    else if (dataType == pyInteger)
        delete valInteger;
    else if (dataType == pyFloatingPoint)
        delete valFloatingPoint;
    else if (dataType == pyString)
        delete valString;

    dataType = pyNone;
}

void BasicVariable::toBool() {
    if (dataType == pyName) {
        delete name;
        valBoolean = false;
    } else if (dataType == pyInteger) {
        valBoolean = !(*valInteger).isZero();
        delete valInteger;
    } else if (dataType == pyFloatingPoint) {
        valBoolean = !((*valFloatingPoint) = 0);
        delete valFloatingPoint;
    } else if (dataType == pyString) {
        valBoolean = !(*valString).empty();
        delete valString;
    } else valBoolean = false;

    dataType = pyBoolean;
}

void BasicVariable::toInt() {
    if (dataType == pyName) {
        delete name;
        valInteger = new HighPrecision(0);
    } else if (dataType == pyBoolean) {
        valInteger = new HighPrecision(valBoolean ? 1 : 0);
        valBoolean = false;
    } else if (dataType == pyFloatingPoint) {
        valInteger = new HighPrecision(int(*valFloatingPoint));
        delete valFloatingPoint;
    } else if (dataType == pyString) {//todo 此处string->int相当于string->bool->int
        valInteger = new HighPrecision((*valString).empty() ? 0 : 1);
        delete valString;
    } else valInteger = new HighPrecision(0);

    dataType = pyInteger;
}

void BasicVariable::toDouble() {
    //todo 待实现toDouble()
}

void BasicVariable::toStr() {
    //todo 待实现toStr()
}