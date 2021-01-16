//
// Created by PaperL on 2021/1/16.
//

#include "Basic.h"

pyFlow::pyFlow(flowType type) : myType(type), returnValue(nullptr) {
    if (myType != pyBreak && myType != pyContinue)
        throw pyException("Unexpected Error in pyFlow Constructor");
}

pyFlow::pyFlow(flowType type, const BasicVariable &arg) : myType(type), returnValue(new BasicVariable(arg)) {
    if (myType != pyReturn)
        throw pyException("Unexpected Error in pyFlow Constructor");
}

pyFlow::~pyFlow() { if (returnValue) delete returnValue; }

pyFlow::flowType pyFlow::getType() const { return myType; }

BasicVariable pyFlow::getReturnValue() const { if (returnValue != nullptr) return (*returnValue); }