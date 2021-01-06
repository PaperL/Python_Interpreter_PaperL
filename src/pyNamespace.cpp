//
// Created by PaperL on 2021/1/5.
//

#include "pyNamespace.h"

pyNamespace::pyNamespace() {
    Python3Parser::FuncdefContext tempFunction();
    tempFunction().getText()

}

BasicVariable pyNamespace::getVariable(const std::string &name, int declareType) {
    auto p = globalVariable.find(name);
    if (p != globalVariable.end())
        return p->second;

    if (!localVariableStack.empty()) {//若为局部变量必在localVariableStack顶部
        p = localVariableStack.top().find(name);
        if (p != localVariableStack.top().end())
            return p->second;
    }

    if (declareType == 0)
        throw pyException("Variable \"" + name + "\" Not Found");
    else if (declareType == 1)
        globalVariable.insert({name, BasicVariable()});
    else if (declareType == 2)
        localVariableStack.top().insert({name, BasicVariable()});
}

void pyNamespace::assignVariable(const std::string &name, const BasicVariable &arg) {
    auto p = globalVariable.find(name);
    if (p != globalVariable.end())
        p->second = arg;

    if (!localVariableStack.empty()) {//若为局部变量必在localVariableStack顶部
        p = localVariableStack.top().find(name);
        if (p != localVariableStack.top().end())
            p->second = arg;
    }

    throw pyException("Variable \"" + name + "\" Not Found");
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