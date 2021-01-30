//
// Created by PaperL on 2021/1/16.
//

#include "Basic.h"

pyFlow::pyFlow(flowType type) : myType(type) {
    if (type == pyReturn)
        returnValue.emplace_back(BasicVariable(BasicVariable::setNone));
}

pyFlow::pyFlow(flowType type, const pyNamespace::valueVector &arg) : myType(type),
                                                                     returnValue(arg) {
    if (type != pyReturn)
        throw pyException("Unexpected Error in pyFlow Constructor");
}

pyFlow::flowType pyFlow::getType() const { return myType; }

pyNamespace::valueVector pyFlow::getReturnValue() const {
    if (myType == pyReturn) return returnValue;
    else throw pyException("Try to Get Return Value of pyFlow of pyBreak/pyContinue");
}