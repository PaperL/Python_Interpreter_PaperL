//
// Created by PaperL on 2021/1/16.
//

#ifndef PYTHON_INTERPRETER_PYFLOW_H
#define PYTHON_INTERPRETER_PYFLOW_H

#include "BasicVariable.h"
#include "robust.h"

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

    explicit pyFlow(flowType type,const BasicVariable &arg);

    ~pyFlow();
};


#endif //PYTHON_INTERPRETER_PYFLOW_H
