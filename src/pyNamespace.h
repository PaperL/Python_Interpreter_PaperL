//
// Created by PaperL on 2021/1/5.
//

#ifndef PYTHON_INTERPRETER_PYNAMESPACE_H
#define PYTHON_INTERPRETER_PYNAMESPACE_H

#include <map>
#include <stack>

#include "Python3BaseVisitor.h"
#include "BasicVariable.h"

typedef std::map<std::string, BasicVariable> variableMap;
typedef std::map<std::string, Python3Parser::FuncdefContext *> functionMap;
typedef std::stack<variableMap> variableStack;

class pyNamespace {
private:
    functionMap stdFunction;
    functionMap userFunction;
    variableMap globalVariable;
    variableStack localVariableStack;
public:
    pyNamespace();//设定stdFunction

    BasicVariable getVariable(const std::string &name);

    void assignVariable(const std::string &name, const BasicVariable &arg, bool autoDeclare = false);

    void defineFunction(const std::string &name, const Python3Parser::FuncdefContext *const arg);

    Python3Parser::FuncdefContext *getFunction(const std::string &name);
};

#endif //PYTHON_INTERPRETER_PYNAMESPACE_H
