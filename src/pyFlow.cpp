//
// Created by PaperL on 2021/1/16.
//

#include "Basic.h"

pyFlow::pyFlow(flowType type) : myType(type) {
    if (type == pyReturn)
        returnValue.emplace_back(BasicVariable(BasicVariable::setNone));
}

pyFlow::pyFlow(flowType type, const pyNamespace::valueVector &arg) : myType(type), //returnValue(nullptr) {
                                                                    returnValue(arg) {
    if (type != pyReturn)
        throw pyException("Unexpected Error in pyFlow Constructor");
    //std::cout << "cp4" << std::endl;
    //returnValue = new pyNamespace::valueVector;
    //*returnValue = arg;
    //std::cout << "cp5" << std::endl;
}

//pyFlow::~pyFlow() {}//if (myType == pyReturn) delete returnValue; }
// 实际上不用 if 语句控制。delete 空指针没有危险

pyFlow::flowType pyFlow::getType() const { return myType; }

pyNamespace::valueVector pyFlow::getReturnValue() const {
    if (myType == pyReturn) return (returnValue);
    else throw pyException("Try to Get Return Value of pyFlow of pyBreak/pyContinue");
}