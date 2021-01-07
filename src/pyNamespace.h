//
// Created by PaperL on 2021/1/5.
//

#ifndef PYTHON_INTERPRETER_PYNAMESPACE_H
#define PYTHON_INTERPRETER_PYNAMESPACE_H

#include <map>
#include <stack>

#include "Python3BaseVisitor.h"
#include "BasicVariable.h"
#include "robust.h"

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

    BasicVariable getVariable(const std::string &name, int declareType = 0);
    //declareType = 0 for not declare, 1 for global, 2 for local

    void assignVariable(const std::string &name, const BasicVariable &arg);//赋值

    BasicVariable getValue(const BasicVariable &arg);


    void defineFunction(const std::string &name, Python3Parser::FuncdefContext *arg);

    Python3Parser::FuncdefContext *getFunction(const std::string &name);
};

#endif //PYTHON_INTERPRETER_PYNAMESPACE_H
