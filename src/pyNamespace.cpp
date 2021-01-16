//
// Created by PaperL on 2021/1/5.
//

#include "Basic.h"

BasicVariable pyNamespace::getVariable(const std::string &name) {
    auto p = globalVariable.find(name);
    if (p != globalVariable.end())
        return p->second;

    if (!localVariableStack.empty()) {//若为局部变量必在localVariableStack顶部
        p = localVariableStack.top().find(name);
        if (p != localVariableStack.top().end())
            return p->second;
    }

    throw pyException("Variable \"" + name + "\" Not Found (getVariable)");
}

void pyNamespace::assignVariable(const std::string &name, const BasicVariable &arg, declareType type) {
    auto p = globalVariable.find(name);
    if (p != globalVariable.end())
        p->second = arg;

    if (!localVariableStack.empty()) {//若为局部变量必在localVariableStack顶部
        p = localVariableStack.top().find(name);
        if (p != localVariableStack.top().end())
            p->second = arg;
    }

    if (type == pyNotDeclare)
        throw pyException("Variable \"" + name + "\" Not Found (assignVariable)");
    else if (type == pyGlobal)
        globalVariable.insert({name, arg});
    else if (type == pyLocal)
        localVariableStack.top().insert({name, arg});
}

BasicVariable pyNamespace::getValue(const BasicVariable &arg) {
    if (arg.getType() == BasicVariable::pyName)
        return getVariable(arg.getName());
    else if (arg.getType() == BasicVariable::pyNull)
        throw pyException("Try to Handle Null BasicVariable as BasicVariable with Name/Value");
    else return arg;
}

void pyNamespace::defineFunction(const std::string &name, Python3Parser::FuncdefContext *arg) {
    /*auto p = stdFunction.find(name);
    if (p != stdFunction.end())
        throw pyException("Redifine Standard Function \"" + name + '\"');*/

    auto p = userFunction.find(name);
    if (p != userFunction.end())
        throw pyException("Redifine Function \"" + name + '\"');

    userFunction.insert({name, arg});
}

Python3Parser::FuncdefContext *pyNamespace::getFunction(const std::string &name) {
    /*auto p = stdFunction.find(name);
    if (p != stdFunction.end())
        return p->second;*/

    auto p = userFunction.find(name);
    if (p != userFunction.end())
        return p->second;

    throw pyException("Function \"" + name + "\" Not Found");
}