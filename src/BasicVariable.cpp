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
    } else if (type == setPositive || type == setNegative) {
        if (dataType != pyBoolean && dataType != pyInteger && dataType != pyFloatingPoint)
            throw pyException("Try to Set Variable of Null/Name/None/String Positive/Negative");
        if (dataType == pyBoolean) {
            dataType = pyInteger;
            valInteger = new HighPrecision(valBoolean ? ((type == setPositive) ? 1 : -1) : 0);
            valBoolean = false;
        } else if (type == setNegative) {
            if (dataType == pyInteger)
                *valInteger = -(*valInteger);
            else if (dataType == pyFloatingPoint)
                *valFloatingPoint = -(*valFloatingPoint);
        }
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

BasicVariable::BasicDataType BasicVariable::getType() const { return dataType; }

std::string &BasicVariable::getName() const {
    if (name == nullptr)
        throw pyException("BasicVariable's Name does not Exist");
    return *name;
}

bool BasicVariable::getBool() const {
    if (dataType != pyBoolean) {
        if (dataType == pyInteger) {
            return !(*valInteger).isZero();
        } else if (dataType == pyFloatingPoint) {
            return ((*valFloatingPoint) != 0);
        } else if (dataType == pyString) {
            return !(*valString).empty();
        } else return false;
    } else return valBoolean;
}

HighPrecision &BasicVariable::getInt() const {
    if (valInteger == nullptr)
        throw pyException("BasicVariable's Integer does not Exist");
    return (*valInteger);
}

double &BasicVariable::getFloat() const {
    if (valFloatingPoint == nullptr)
        throw pyException("BasicVariable's FloatingPoint do not Exist");
    return (*valFloatingPoint);
}

std::string &BasicVariable::getString() const {
    if (valString == nullptr)
        throw pyException("BasicVariable's String do not Exist");
    return (*valString);
}

/*std::istream &operator>>(std::istream &in, BasicVariable &arg) {

    return in;
}*/

std::ostream &operator<<(std::ostream &out, const BasicVariable &arg) {
    if (arg.dataType == BasicVariable::pyNull)
        throw pyException("Try to Output Null Variable");
    else if (arg.dataType == BasicVariable::pyName)
        throw pyException("Try to Output Variable's Name");
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
    if (this->dataType == pyNull || this->dataType == pyName
        || arg.dataType == pyNull || arg.dataType == pyName)
        throw pyException("Try to Compare Variables of Null/Name Type (in operator==)");
    if (this->dataType == pyNone || arg.dataType == pyNone)
        return (this->dataType == arg.dataType);
    if (this->dataType == pyString || arg.dataType == pyString) {
        if (this->dataType != arg.dataType)
            return false;
        return ((*this).getString() == arg.getString());
    }
    if (this->dataType == pyFloatingPoint || arg.dataType == pyFloatingPoint) {
        BasicVariable temp1(*this), temp2(arg);
        return (temp1.toFloat().getFloat() == temp2.toFloat().getFloat());
    } else {
        BasicVariable temp1(*this), temp2(arg);
        return (temp1.toInt().getInt() == temp2.toInt().getInt());
    }
}

bool BasicVariable::operator!=(const BasicVariable &arg) const { return !((*this) == arg); }

bool BasicVariable::operator<(const BasicVariable &arg) const {
    if (this->dataType == pyNull || this->dataType == pyName || this->dataType == pyNone
        || arg.dataType == pyNull || arg.dataType == pyName || arg.dataType == pyNone)//正列举更合理，参见operator+
        throw pyException("Try to Compare Variables of Null/Name/None Type");
    if (this->dataType == pyString || arg.dataType == pyString) {
        if (this->dataType == arg.dataType)
            return (*(this->valString) < *(arg.valString));
        else throw pyException("Try to Compare Variables of String and Other Type");
    }
    if (this->dataType == pyFloatingPoint || arg.dataType == pyFloatingPoint) {
        BasicVariable temp1(*this), temp2(arg);//特判一下this->dataType == arg.dataType可以优化，参见operator+
        return (temp1.toFloat().getFloat() < temp2.toFloat().getFloat());
    } else {
        BasicVariable temp1(*this), temp2(arg);
        return (temp1.toInt().getInt() < temp2.toInt().getInt());
    }
}

bool BasicVariable::operator<=(const BasicVariable &arg) const {
    if (this->dataType == pyNull || this->dataType == pyName || this->dataType == pyNone
        || arg.dataType == pyNull || arg.dataType == pyName || arg.dataType == pyNone)
        throw pyException("Try to Compare Variables of Null/Name/None Type");
    if (this->dataType == pyString || arg.dataType == pyString) {
        if (this->dataType == arg.dataType)
            return (*(this->valString) <= *(arg.valString));
        else throw pyException("Try to Compare Variables of String and Other Type");
    }
    if (this->dataType == pyFloatingPoint || arg.dataType == pyFloatingPoint) {
        BasicVariable temp1(*this), temp2(arg);
        return (temp1.toFloat().getFloat() <= temp2.toFloat().getFloat());
    } else {
        BasicVariable temp1(*this), temp2(arg);
        return (temp1.toInt().getInt() <= temp2.toInt().getInt());
    }
}

bool BasicVariable::operator>(const BasicVariable &arg) const { return !((*this) <= arg); }

bool BasicVariable::operator>=(const BasicVariable &arg) const { return !((*this) < arg); }

BasicVariable BasicVariable::operator+() const { return BasicVariable(*this, setPositive); }

BasicVariable BasicVariable::operator-() const { return BasicVariable(*this, setNegative); }

BasicVariable BasicVariable::operator+(const BasicVariable &arg) const {
    if (this->dataType != pyBoolean && this->dataType != pyInteger
        && this->dataType == pyFloatingPoint && this->dataType != pyString
        && arg.dataType != pyBoolean && arg.dataType != pyInteger
        && arg.dataType == pyFloatingPoint && arg.dataType != pyString)
        throw pyException("Try to Plus Variables of Null/Name/None Type");

    if (this->dataType == pyString) {
        if (this->dataType == arg.dataType)
            return BasicVariable((*valString) + (*arg.valString));
        else throw pyException("Try to Plus String Variable with Other Type Variable");
    }

    if (this->dataType == pyFloatingPoint || arg.dataType == pyFloatingPoint) {
        if (this->dataType != pyFloatingPoint) {
            BasicVariable temp(*this);
            return BasicVariable(temp.toFloat().getFloat() + arg.getFloat());
        } else if (arg.dataType != pyFloatingPoint) {
            BasicVariable temp(arg);
            return BasicVariable((*this).getFloat() + temp.toFloat().getFloat());
        } else return BasicVariable(this->getFloat() + arg.getFloat());
    } else {
        if (this->dataType == pyBoolean && arg.dataType == pyBoolean)
            return BasicVariable(HighPrecision(this->getBool() ? 1 : 0) + HighPrecision(arg.getBool() ? 1 : 0));
        else if (this->dataType == pyBoolean)
            return BasicVariable(HighPrecision(this->getBool() ? 1 : 0) + arg.getInt());
        else if (arg.dataType == pyBoolean)
            return BasicVariable(this->getInt() + HighPrecision(arg.getBool() ? 1 : 0));
        else return BasicVariable(this->getInt() + arg.getInt());
    }
}

BasicVariable BasicVariable::operator-(const BasicVariable &arg) const {
    if (this->dataType != pyBoolean && this->dataType != pyInteger && this->dataType == pyFloatingPoint
        && arg.dataType != pyBoolean && arg.dataType != pyInteger && arg.dataType == pyFloatingPoint)
        throw pyException("Try to Minus Variables of Null/Name/None/String Type");

    if (this->dataType == pyFloatingPoint || arg.dataType == pyFloatingPoint) {
        if (this->dataType != pyFloatingPoint) {
            BasicVariable temp(*this);
            return BasicVariable(temp.toFloat().getFloat() - arg.getFloat());
        } else if (arg.dataType != pyFloatingPoint) {
            BasicVariable temp(arg);
            return BasicVariable((*this).getFloat() - temp.toFloat().getFloat());
        } else return BasicVariable(this->getFloat() - arg.getFloat());
    } else {
        if (this->dataType == pyBoolean && arg.dataType == pyBoolean)
            return BasicVariable(HighPrecision(this->getBool() ? 1 : 0) - HighPrecision(arg.getBool() ? 1 : 0));
        else if (this->dataType == pyBoolean)
            return BasicVariable(HighPrecision(this->getBool() ? 1 : 0) - arg.getInt());
        else if (arg.dataType == pyBoolean)
            return BasicVariable(this->getInt() - HighPrecision(arg.getBool() ? 1 : 0));
        else return BasicVariable(this->getInt() - arg.getInt());
    }
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

BasicVariable &BasicVariable::toNone() {
    if (dataType == pyNone)return (*this);

    if (dataType == pyName)
        delete name;
    else if (dataType == pyInteger)
        delete valInteger;
    else if (dataType == pyFloatingPoint)
        delete valFloatingPoint;
    else if (dataType == pyString)
        delete valString;

    dataType = pyNone;

    return (*this);
}

BasicVariable &BasicVariable::toBool() {
    if (dataType == pyBoolean)return (*this);

    if (dataType == pyNone)
        valBoolean = false;
    else if (dataType == pyInteger) {
        valBoolean = bool(*valInteger);
        delete valInteger;
    } else if (dataType == pyFloatingPoint) {
        valBoolean = ((*valFloatingPoint) != 0);
        delete valFloatingPoint;
    } else if (dataType == pyString) {
        valBoolean = !(*valString).empty();
        delete valString;
    } else throw pyException("Try to Convert Variable of Null/Name to Bool");

    dataType = pyBoolean;

    return (*this);
}

BasicVariable &BasicVariable::toInt() {
    if (dataType == pyInteger)return (*this);

    if (dataType == pyBoolean) {
        valInteger = new HighPrecision(valBoolean ? 1 : 0);
        valBoolean = false;
    } else if (dataType == pyFloatingPoint) {
        valInteger = new HighPrecision(int(*valFloatingPoint));
        delete valFloatingPoint;
    } else if (dataType == pyString) {//此处string->int相当于string->bool->int
        valInteger = new HighPrecision((*valString).empty() ? 0 : 1);
        delete valString;
    } else throw pyException("Try to Convert Variable of Null/Name/None to Integer");

    dataType = pyInteger;

    return (*this);
}

BasicVariable &BasicVariable::toFloat() {
    if (dataType == pyFloatingPoint)return (*this);

    if (dataType == pyBoolean) {
        valFloatingPoint = new double(valBoolean ? 1.0 : 0.0);
        valBoolean = false;
    } else if (dataType == pyInteger) {
        valFloatingPoint = new double(double(*valInteger));//todo 为什么此处不new double(*arg)不会报错？？？
        delete valInteger;
    } else if (dataType == pyString) {
        valFloatingPoint = new double((*valString).empty() ? 0.0 : 1.0);
        delete valString;
    } else throw pyException("Try to Convert Variable of Null/Name/None to Float");

    dataType = pyFloatingPoint;

    return (*this);
}

BasicVariable &BasicVariable::toStr() {
    if (dataType == pyString)return (*this);

    if (dataType == pyNone)
        valString = new std::string("None");
    else if (dataType == pyBoolean) {
        valString = new std::string(valBoolean ? "True" : "False");
        valBoolean = false;
    } else if (dataType == pyInteger) {
        valString = new std::string(std::string(*valInteger));//todo 此处IDE无法正常跳转类型转换函数
        delete valInteger;
    } else if (dataType == pyFloatingPoint) {
        std::stringstream ss;
        ss << (*valFloatingPoint);
        valString = new std::string(ss.str());
        delete valFloatingPoint;
    } else throw pyException("Try to Convert Variable of Null/Name to String");

    dataType = pyString;

    return (*this);
}

bool BasicVariable::isNull() { return dataType == pyNull; }