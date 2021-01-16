//
// Created by PaperL on 2021/1/5.
//

#ifndef PYTHON_INTERPRETER_BASIC_H
#define PYTHON_INTERPRETER_BASIC_H


#include <iostream>

#include "robust.h"

//----------BasicVariable----------
#include <string>
#include <sstream>//double to string

#include "HighPrecision.h"

//-----------pyNamespace-----------
#include <map>
#include <stack>

#include "Python3BaseVisitor.h"

//=================================
//========  BasicVariable  ========
//=================================

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

    BasicVariable evenlyDivide(const BasicVariable &arg) const;

    BasicVariable operator%(const BasicVariable &arg) const;

    BasicVariable operator+=(const BasicVariable &arg);

    BasicVariable operator-=(const BasicVariable &arg);

    BasicVariable operator*=(const BasicVariable &arg);

    BasicVariable operator/=(const BasicVariable &arg);

    BasicVariable enenlyDivideEqual(const BasicVariable &arg);

    BasicVariable operator%=(const BasicVariable &arg);


    BasicVariable &toNone();

    BasicVariable &toBool();

    BasicVariable &toInt();

    BasicVariable &toFloat();

    BasicVariable &toStr();


    bool isNull() const;
};



//=================================
//=========  pyNamespace  =========
//=================================

typedef std::map<std::string, BasicVariable> variableMap;
typedef std::map<std::string, Python3Parser::FuncdefContext *> functionMap;
typedef std::stack<variableMap> variableStack;

class pyNamespace {
private:
    //functionMap stdFunction;
    functionMap userFunction;
    variableMap globalVariable;
    variableStack localVariableStack;
public:

    enum declareType {
        pyNotDeclare, pyGlobal, pyLocal
    };

    BasicVariable getVariable(const std::string &name);


    void assignVariable(const std::string &name, const BasicVariable &arg, declareType type = pyNotDeclare);
    //赋值

    BasicVariable getValue(const BasicVariable &arg);


    void defineFunction(const std::string &name, Python3Parser::FuncdefContext *arg);

    Python3Parser::FuncdefContext *getFunction(const std::string &name);
};



//=================================
//===========  pyFlow  ============
//=================================

class pyFlow {
public:
    enum flowType {
        pyBreak, pyContinue, pyReturn
    };

private:
    flowType myType;
    BasicVariable *returnValue;

public:
    explicit pyFlow(flowType type);

    explicit pyFlow(flowType type, const BasicVariable &arg);

    ~pyFlow();

    flowType getType() const;

    BasicVariable getReturnValue() const;
};


#endif //PYTHON_INTERPRETER_BASIC_H
