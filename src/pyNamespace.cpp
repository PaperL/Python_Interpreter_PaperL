//
// Created by PaperL on 2021/1/5.
//

#include "Basic.h"

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
    auto &localVariable = VariableStack.back();

    auto p = globalVariable.find(name);
    if (p != globalVariable.end()) {
        globalVariable.erase(p);
        globalVariable.insert(std::make_pair(name, arg));
        //p->second = arg;
        return;
    }

    if (VariableStack.size() > 1) {
        p = localVariable.find(name);
        if (p != localVariable.end()) {
            localVariable.erase(p);
            localVariable.insert(std::make_pair(name, arg));
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

void pyNamespace::defineFunction(const std::string &name, Python3Parser::SuiteContext *funcCtx,
                                 const variableVector &parameters) {
    auto p = userFunction.find(name);
    if (p != userFunction.end())
        throw pyException("Redifine Function \"" + name + '\"');

    userFunction.insert(std::make_pair(name, std::make_pair(funcCtx, parameters)));
}

Python3Parser::SuiteContext *pyNamespace::loadFunction(const std::string &name, const variableVector &parameters) {
    auto p = userFunction.find(name);
    if (p != userFunction.end()) {
        const auto &functionParameter = p->second.second;
        // 进入函数时将参数列表作为局部变量空间
        variableMap localVariableMap;
        // 先载入函数所有参数
        for (const auto &i:functionParameter)
            localVariableMap.insert(std::make_pair(i.first, i.second));
        // 以输入参数覆盖
        int i = 0;
        // position argument
        for (; i < parameters.size(); ++i) {
            if (parameters[i].first.empty()) {
                auto p2 = localVariableMap.find(functionParameter[i].first);
                localVariableMap.erase(p2);
                localVariableMap.insert(std::make_pair(functionParameter[i].first, parameters[i].second));
            } else break;
        }
        // keyword argument
        for (; i < parameters.size(); ++i) {
            if (parameters[i].first.empty())
                throw pyException("Get Keyword Argument ahead of Positional Argument");
            auto p2 = localVariableMap.find(parameters[i].first);
            if (p2 == localVariableMap.end())
                throw pyException("Get Wrong Keyword Argument");
            localVariableMap.erase(p2);
            localVariableMap.insert(std::make_pair(parameters[i].first, parameters[i].second));
        }

        VariableStack.emplace_back(localVariableMap);
        return p->second.first;
    }
    throw pyException("Function \"" + name + "\" Not Found");
}

void pyNamespace::unloadFunction() {
    //if(VariableStack.size()>1)
    VariableStack.pop_back();
}