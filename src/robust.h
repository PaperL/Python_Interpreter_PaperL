//
// Created by PaperL on 2021/1/6.
//

#ifndef PYTHON_INTERPRETER_ROBUST_H
#define PYTHON_INTERPRETER_ROBUST_H

//#define debug_info

#include <cstdio>//perror
#include <string>
#include <exception>

// 良好的代码习惯应是从 std::exception 继承
class pyException : public std::exception {
public:
    std::string pyErrorInfo;

    pyException(std::string arg = "No ErrorInfo pyException") : pyErrorInfo(arg) {
        perror(arg.c_str());
    }
};

#endif //PYTHON_INTERPRETER_ROBUST_H
