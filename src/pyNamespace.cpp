//
// Created by PaperL on 2021/1/5.
//

#include "Basic.h"

pyNamespace::functionInfo::functionInfo(Python3Parser::FuncdefContext *funcCtx, const parameterVector &parameters)
        : functionCtx(funcCtx) {
    for(auto i:parameters)
        functionParameter.insert(std::make_pair(i.first.getName(),i.second));
}

pyNamespace::pyNamespace() { VariableStack.emplace_back(variableMap()); }

BasicVariable pyNamespace::getVariable(const std::string &name) {
    auto &globalVariable = VariableStack.front();// VariableStack 底层为全局变量
    auto p = globalVariable.find(name);
    if (p != globalVariable.end())
        return p->second;

    if (VariableStack.size() > 1) {
        auto &localVariableStack = VariableStack.back();
        p = localVariableStack.find(name);
        if (p != localVariableStack.end())
            return p->second;
    }
    throw pyException("Variable \"" + name + "\" Not Found (getVariable)");
}

void pyNamespace::assignVariable(const std::string &name, const BasicVariable &arg, declareType type) {
    auto &globalVariable = VariableStack.front();

    auto p = globalVariable.find(name);
    if (p != globalVariable.end()) {
        p->second = arg;
        return;
    }

    if (VariableStack.size() > 1) {
        auto &localVariableStack = VariableStack.back();
        p = localVariableStack.find(name);
        if (p != localVariableStack.end()) {
            p->second = arg;
            return;
        }
    }

    if (type == pyNotDeclare)
        throw pyException("Variable \"" + name + "\" Not Found (assignVariable)");
    else if (type == pyGlobal)
        globalVariable.insert(std::make_pair(name, arg));
    else if (type == pyLocal)
        VariableStack.back().insert(std::make_pair(name, arg));
}

BasicVariable pyNamespace::getValue(const BasicVariable &arg) {
    if (arg.getType() == BasicVariable::pyName)
        return getVariable(arg.getName());
    else if (arg.getType() == BasicVariable::pyNull)
        throw pyException("Try to Handle Null BasicVariable as BasicVariable with Name/Value");
    else return arg;
}

void pyNamespace::defineFunction(const std::string &name, Python3Parser::FuncdefContext *funcCtx,
                                 const parameterVector &parameters) {
    auto p = userFunction.find(name);
    if (p != userFunction.end())
        throw pyException("Redifine Function \"" + name + '\"');

    userFunction.insert(std::make_pair(name, functionInfo(funcCtx, parameters)));
}

Python3Parser::FuncdefContext *pyNamespace::loadFunction(const std::string &name) {
    auto p = userFunction.find(name);
    if (p != userFunction.end()) {
        // 进入函数时将参数列表作为局部变量空间
        VariableStack.emplace_back(p->second.functionParameter);
        return p->second.functionCtx;
    }

    throw pyException("Function \"" + name + "\" Not Found");
}

void pyNamespace::unloadFunction() {
    //if(VariableStack.size()>1)
    VariableStack.pop_back();
}