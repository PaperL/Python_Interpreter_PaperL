//
// Created by PaperL on 2021/1/6.
//

#ifndef PYTHON_INTERPRETER_ROBUST_H
#define PYTHON_INTERPRETER_ROBUST_H

#define debug_info

#include <string>

class pyException {
public:
    std::string errInfo;

    pyException(std::string arg = "null") : errInfo(arg) {}
};

#endif //PYTHON_INTERPRETER_ROBUST_H
