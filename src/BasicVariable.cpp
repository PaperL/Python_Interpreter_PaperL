//
// Created by PaperL on 2020/12/10.
//

#include "BasicVariable.h"

void BasicVariable::strGet(const std::string &arg) {

}

std::string BasicVariable::strShow() {

}

void BasicVariable::print() const {

}

BasicVariable::BasicVariable(const BasicVariable &arg, ConstructorType type) : dataType(arg.dataType),
                                                                               declared(arg.declared),
                                                                               valBoolean(arg.valBoolean),
                                                                               valInteger(arg.valInteger),
                                                                               valFloatingPoint(arg.valFloatingPoint),
                                                                               valString(arg.valString) {
    if (type != nullSetting) {
        if (type == setNegation) {
            if (dataType == pyBoolean)
                valBoolean = !valBoolean;
        } else if (type == setNegative) {
            if (dataType == pyInteger && valInteger != nullptr)
                *valInteger = -(*valInteger);
            else if (dataType == pyFloatingPoint && valFloatingPoint != nullptr)
                *valFloatingPoint = -(*valFloatingPoint);
        }
    }
}

template<class T>
BasicVariable::BasicVariable(BasicDataType type, T &context): dataType(type), declared(false),
                                                              valBoolean(false), valInteger(nullptr),
                                                              valFloatingPoint(nullptr), valString(nullptr) {
    if (type != pyNone && context != nullptr) {
        if (type == pyBoolean)
            valBoolean = *context;
        else if (type == pyInteger) {
            valInteger = new HighPrecision;
            *valInteger = context;
        } else if (type == pyFloatingPoint) {
            valFloatingPoint = new double;
            *valFloatingPoint = context;
        } else if (type == pyString) {
            valString = new std::string;
            *valString = context;
        }
    }
}

BasicVariable::~BasicVariable() {

}

std::istream &operator>>(std::istream &in, HighPrecision &arg) {

    return in;
}

std::ostream &operator<<(std::ostream &out, const HighPrecision &arg) {

    return out;
}

BasicVariable &BasicVariable::operator=(const BasicVariable &arg) {

    return *this;
}

BasicVariable &BasicVariable::operator[](BasicVariable &arg) const {

}

BasicVariable BasicVariable::operator!() const {

}

BasicVariable BasicVariable::operator&&(const BasicVariable &arg) const {

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

}

BasicVariable BasicVariable::operator-(const BasicVariable &arg) const {

}

BasicVariable BasicVariable::operator*(const BasicVariable &arg) const {

}

BasicVariable BasicVariable::operator/(const BasicVariable &arg) const {

}

BasicVariable BasicVariable::operator%(const BasicVariable &arg) const {

}