//
// Created by PaperL on 2020/12/10.
//

#include "Basic.h"

void BasicVariable::destroy() {
    dataType = pyNull;
    valBoolean = false;
    delete name;
    delete valInteger;
    delete valFloatingPoint;
    delete valString;
    name = nullptr;
    valInteger = nullptr;
    valFloatingPoint = nullptr;
    valString = nullptr;
}

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
                                                                               valBoolean(arg.valBoolean),
                                                                               name(nullptr),
                                                                               valInteger(nullptr),
                                                                               valFloatingPoint(nullptr),
                                                                               valString(nullptr) {
    if (arg.name)name = new std::string(*arg.name);
    if (arg.valInteger)valInteger = new HighPrecision(*arg.valInteger);
    if (arg.valFloatingPoint)valFloatingPoint = new double(*arg.valFloatingPoint);
    if (arg.valString)valString = new std::string(*arg.valString);

    if (type == setNegation) {
        if (dataType == pyBoolean)
            valBoolean = !valBoolean;
        else throw pyException("Try to set not pyBoolean Value Negation");
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

BasicVariable::~BasicVariable() { destroy(); }

BasicVariable::BasicDataType BasicVariable::getType() const { return dataType; }

std::string BasicVariable::getName() const {
    if (this->dataType != pyName || name == nullptr)
        throw pyException("BasicVariable's Name does not Exist");
    return *name;
}

bool BasicVariable::getBool() const {
    if (dataType != pyBoolean)
        throw pyException("BasicVariable's Boolean does not Exist");
    else return valBoolean;
}

HighPrecision BasicVariable::getInt() const {
    if (this->dataType != pyInteger || valInteger == nullptr)
        throw pyException("BasicVariable's Integer does not Exist");
    return (*valInteger);
}

double BasicVariable::getFloat() const {
    if (this->dataType != pyFloatingPoint || valFloatingPoint == nullptr)
        throw pyException("BasicVariable's FloatingPoint do not Exist");
    return (*valFloatingPoint);
}

std::string BasicVariable::getString() const {
    if (this->dataType != pyString || valString == nullptr)
        throw pyException("BasicVariable's String do not Exist");
    return (*valString);
}

std::ostream &operator<<(std::ostream &out, const BasicVariable &arg) {
    if (arg.dataType == BasicVariable::pyNull)
        throw pyException("Try to Output Null Variable");
    else if (arg.dataType == BasicVariable::pyName)
        throw pyException("Try to Output Variable's Name: \"" + arg.getName() + '\"');
    else if (arg.dataType == BasicVariable::pyNone)
        std::cout << "None";
    else if (arg.dataType == BasicVariable::pyBoolean)
        std::cout << (arg.valBoolean ? "True" : "False");
    else if (arg.dataType == BasicVariable::pyInteger)
        std::cout << *(arg.valInteger);
    else if (arg.dataType == BasicVariable::pyFloatingPoint)
        printf("%.6lf", *(arg.valFloatingPoint));
        //std::cout << *(arg.valFloatingPoint);
    else if (arg.dataType == BasicVariable::pyString)
        std::cout << *(arg.valString);
    return out;
}

BasicVariable &BasicVariable::operator=(const BasicVariable &arg) {
    if (this == &arg)return (*this);
    destroy();
    dataType = arg.dataType;
    if (dataType == pyName)
        name = new std::string(*arg.name);
    else if (dataType == pyBoolean)
        valBoolean = arg.valBoolean;
    else if (dataType == pyInteger)
        valInteger = new HighPrecision(*arg.valInteger);
    else if (dataType == pyFloatingPoint)
        valFloatingPoint = new double(*arg.valFloatingPoint);
    else if (dataType == pyString)
        valString = new std::string(*arg.valString);

    return *this;
}

char BasicVariable::operator[](const int index) const {
    if (dataType == pyString && index >= 0 && index < valString->length())
        return (*valString)[index];
    else throw pyException("Use Not-string Variable's operator[]");
}

BasicVariable BasicVariable::operator!() const {
    if (dataType == pyBoolean)
        return BasicVariable(*this, setNegation);
    else {
        throw pyException("Warning: Use Not-boolean Variable's operator \"!\"");
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
        throw pyException("Try to Compare Variables of Null/Name Type (in operator ==)");
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
        && this->dataType != pyFloatingPoint && this->dataType != pyString
        && arg.dataType != pyBoolean && arg.dataType != pyInteger
        && arg.dataType != pyFloatingPoint && arg.dataType != pyString)
        throw pyException("Try to Plus Variables of Null/Name/None Type");

    if (this->dataType == pyString || arg.dataType == pyString) {
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
    if (this->dataType != pyBoolean && this->dataType != pyInteger && this->dataType != pyFloatingPoint
        && arg.dataType != pyBoolean && arg.dataType != pyInteger && arg.dataType != pyFloatingPoint)
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
    if (this->dataType != pyBoolean && this->dataType != pyInteger
        && this->dataType != pyFloatingPoint && this->dataType != pyString
        && arg.dataType != pyBoolean && arg.dataType != pyInteger
        && arg.dataType != pyFloatingPoint && arg.dataType != pyString)
        throw pyException("Try to Multiply Variables of Null/Name/None Type");

    if (this->dataType == pyString || arg.dataType == pyString) {
        if (this->dataType == pyString && (arg.dataType == pyBoolean || arg.dataType == pyInteger)) {
            BasicVariable boundary = arg;
            boundary.toInt();
            BasicVariable ret((std::string()));
            for (BasicVariable i(HighPrecision(0));
                 i.getInt() < boundary.getInt();
                 i = i + BasicVariable(HighPrecision(1)))//todo 可优化常数(HighPrecision++)
                ret += (*this);
            return ret;
        } else if (arg.dataType == pyString && (this->dataType == pyBoolean || this->dataType == pyInteger)) {
            BasicVariable boundary = (*this);
            boundary.toInt();
            BasicVariable ret((std::string()));
            for (BasicVariable i(HighPrecision(0));
                 i.getInt() < boundary.getInt();
                 i = i + BasicVariable(HighPrecision(1)))
                ret += arg;
            return ret;
        } else throw pyException("Try to Multiply String Variable with Float/String Type Variable");
    }

    if (this->dataType == pyFloatingPoint || arg.dataType == pyFloatingPoint) {
        if (this->dataType != pyFloatingPoint) {
            BasicVariable temp(*this);
            return BasicVariable(temp.toFloat().getFloat() * arg.getFloat());
        } else if (arg.dataType != pyFloatingPoint) {
            BasicVariable temp(arg);
            return BasicVariable((*this).getFloat() * temp.toFloat().getFloat());
        } else return BasicVariable(this->getFloat() * arg.getFloat());
    } else {
        if (this->dataType == pyBoolean && arg.dataType == pyBoolean)
            return BasicVariable(HighPrecision(this->getBool() ? 1 : 0) * HighPrecision(arg.getBool() ? 1 : 0));
        else if (this->dataType == pyBoolean)
            return BasicVariable(HighPrecision(this->getBool() ? 1 : 0) * arg.getInt());
        else if (arg.dataType == pyBoolean)
            return BasicVariable(this->getInt() * HighPrecision(arg.getBool() ? 1 : 0));
        else return BasicVariable(this->getInt() * arg.getInt());
    }
}

BasicVariable BasicVariable::operator/(const BasicVariable &arg) const {
    if (this->dataType != pyBoolean && this->dataType != pyInteger && this->dataType != pyFloatingPoint
        && arg.dataType != pyBoolean && arg.dataType != pyInteger && arg.dataType != pyFloatingPoint)
        throw pyException("Try to Divide Variables of Null/Name/None/String Type");

    BasicVariable tempThis = *this, tempArg = arg;
    tempThis.toFloat(), tempArg.toFloat();
    return BasicVariable(tempThis.getFloat() / tempArg.getFloat());
}

BasicVariable BasicVariable::evenlyDivide(const BasicVariable &arg) const {
    if (this->dataType != pyBoolean && this->dataType != pyInteger
        && arg.dataType != pyBoolean && arg.dataType != pyInteger)
        throw pyException("Try to Divide Variables of Null/Name/None/Float/String Type");

    if (this->dataType == pyBoolean && arg.dataType == pyBoolean)
        return BasicVariable(HighPrecision(this->getBool() ? 1 : 0) / HighPrecision(arg.getBool() ? 1 : 0));
    else if (this->dataType == pyBoolean)
        return BasicVariable(HighPrecision(this->getBool() ? 1 : 0) / arg.getInt());
    else if (arg.dataType == pyBoolean)
        return BasicVariable(this->getInt() / HighPrecision(arg.getBool() ? 1 : 0));
    else {
        return BasicVariable(this->getInt() / arg.getInt());
    }
}

BasicVariable BasicVariable::operator%(const BasicVariable &arg) const {
    if (this->dataType != pyBoolean && this->dataType != pyInteger
        && arg.dataType != pyBoolean && arg.dataType != pyInteger)
        throw pyException("Try to Modulo Variables of Null/Name/None/Float/String Type");

    if (this->dataType == pyBoolean && arg.dataType == pyBoolean)
        return BasicVariable(HighPrecision(this->getBool() ? 1 : 0) % HighPrecision(arg.getBool() ? 1 : 0));
    else if (this->dataType == pyBoolean)
        return BasicVariable(HighPrecision(this->getBool() ? 1 : 0) % arg.getInt());
    else if (arg.dataType == pyBoolean)
        return BasicVariable(this->getInt() % HighPrecision(arg.getBool() ? 1 : 0));
    else return BasicVariable(this->getInt() % arg.getInt());
}

BasicVariable BasicVariable::operator+=(const BasicVariable &arg) {
    (*this) = (*this) + arg;
    return (*this);
}

BasicVariable BasicVariable::operator-=(const BasicVariable &arg) {
    (*this) = (*this) - arg;
    return (*this);
}

BasicVariable BasicVariable::operator*=(const BasicVariable &arg) {
    (*this) = (*this) * arg;
    return (*this);
}

BasicVariable BasicVariable::operator/=(const BasicVariable &arg) {
    (*this) = (*this) / arg;
    return (*this);
}

BasicVariable BasicVariable::enenlyDivideEqual(const BasicVariable &arg) {
    (*this) = this->evenlyDivide(arg);
    return (*this);
}

BasicVariable BasicVariable::operator%=(const BasicVariable &arg) {
    (*this) = (*this) % arg;
    return (*this);
}

BasicVariable &BasicVariable::toNone() {
    if (dataType == pyNone)return (*this);

    destroy();
    dataType = pyNone;

    return (*this);
}

BasicVariable &BasicVariable::toBool() {
    if (dataType == pyBoolean)return (*this);
    bool tempAns;

    if (dataType == pyNone) tempAns = false;
    else if (dataType == pyInteger) tempAns = bool(*valInteger);
    else if (dataType == pyFloatingPoint) tempAns = ((*valFloatingPoint) != 0);
    else if (dataType == pyString) tempAns = !(*valString).empty();
    else throw pyException("Try to Convert Variable of Null/Name to Bool");

    destroy();
    dataType = pyBoolean;
    valBoolean = tempAns;

    return (*this);
}

BasicVariable &BasicVariable::toInt() {
    if (dataType == pyInteger)return (*this);
    HighPrecision tempAns;

    if (dataType == pyBoolean) tempAns = HighPrecision(valBoolean ? 1 : 0);
    else if (dataType == pyFloatingPoint) tempAns = HighPrecision(int(*valFloatingPoint));
    else if (dataType == pyString) {
        // 此处 string->int 相当于 string->bool->int
        // 修正: string 可以转成 int 情况下优先按数码转换
        //      以及可能不存在自动的 string->bool->int 转化
        bool stringToIntFlag = true;
        for (auto i:(*valString)) {
            if ((i < '0' || i > '9') && i != '-') {
                stringToIntFlag = false;
                break;
            }
        }
        if (stringToIntFlag) tempAns = HighPrecision(*valString);
        else tempAns = HighPrecision((*valString).empty() ? 0 : 1);
    } else throw pyException("Try to Convert Variable of Null/Name/None to Integer");

    destroy();
    dataType = pyInteger;
    valInteger = new HighPrecision(tempAns);

    return (*this);
}

BasicVariable &BasicVariable::toFloat() {
    if (dataType == pyFloatingPoint)return (*this);
    double tempAns;

    if (dataType == pyBoolean) tempAns = valBoolean ? 1.0 : 0.0;
    else if (dataType == pyInteger) tempAns = double(*valInteger);
    else if (dataType == pyString) tempAns = (*valString).empty() ? 0.0 : 1.0;
    else throw pyException("Try to Convert Variable of Null/Name/None to Float");

    destroy();
    dataType = pyFloatingPoint;
    valFloatingPoint = new double(tempAns);

    return (*this);
}

BasicVariable &BasicVariable::toStr() {
    if (dataType == pyString)return (*this);
    std::string tempAns;

    if (dataType == pyNone) tempAns = "None";
    else if (dataType == pyBoolean)
        tempAns = valBoolean ? "True" : "False";
    else if (dataType == pyInteger)
        tempAns = std::string(*valInteger);// 此处IDE无法正常跳转类型转换函数?
    else if (dataType == pyFloatingPoint) {
        //std::stringstream ss;
        //ss << (*valFloatingPoint);
        //tempAns = ss.str();
        // 需用 cout<<setiosflags(ios::fixed)<<setprecision(6); 控制小数点后位数
        // 需要头文件 #include <iomanip>
        char ss[32];
        // sprintf(ss,"%g",*valFloatingPoint); 自动去除末尾0
        sprintf(ss, "%.6lf", *valFloatingPoint);
        tempAns = ss;
    } else throw pyException("Try to Convert Variable of Null/Name to String");

    destroy();
    dataType = pyString;
    valString = new std::string(tempAns);

    return (*this);
}

bool BasicVariable::isNull() const { return (dataType == pyNull); }