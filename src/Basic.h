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

class pyNamespace {
public:
    typedef std::map<std::string, BasicVariable> variableMap;
    typedef std::vector<std::pair<std::string, BasicVariable> > parameterVector;

    class functionInfo {
    public:
        Python3Parser::SuiteContext *functionSuite;
        variableMap functionParameter;

        functionInfo(Python3Parser::SuiteContext *funcCtx, const parameterVector &parameters);
    };

    typedef std::map<std::string, functionInfo> functionMap;
    typedef std::vector<variableMap> variableVector;

private:
    functionMap userFunction;
    variableVector VariableStack;

public:
    enum declareType {
        pyNotDeclare, pyGlobal, pyLocal
    };

    pyNamespace();

    BasicVariable getVariable(const std::string &name);


    void assignVariable(const std::string &name, const BasicVariable &arg, declareType type = pyNotDeclare);
    //赋值

    BasicVariable getValue(const BasicVariable &arg);
    //若为 pyName 类型则获取其值, 否则返回原参数

    void defineFunction(const std::string &name, Python3Parser::SuiteContext *funcCtx,
                        const parameterVector &parameters = parameterVector());

    Python3Parser::SuiteContext *loadFunction(const std::string &name);

    void unloadFunction();
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
