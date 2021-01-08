#include <iostream>

#include "antlr4-runtime.h"
#include "Python3Lexer.h"
#include "Python3Parser.h"
#include "Evalvisitor.h"

using namespace antlr4;

int main(int argc, const char *argv[]) {
    ANTLRInputStream input(std::cin);
    Python3Lexer lexer(&input);
    CommonTokenStream tokens(&lexer);
    tokens.fill();
    Python3Parser parser(&tokens);
    tree::ParseTree *tree = parser.file_input();
    try {
        EvalVisitor visitor;
        visitor.visit(tree);
    } catch (pyException &exception) {
        perror(exception.errInfo.c_str());
    }

    /*const std::string filepath=argv[1];
    std::ifstream ifs;
    ifs.open(filepath);
    if (!ifs.good()) {
        std::cout<<"bad";
    }
    ANTLRInputStream input(ifs);
    Python3Lexer lexer(&input);
    CommonTokenStream tokens(&lexer);
    tokens.fill();
    Python3Parser parser(&tokens);
    tree::ParseTree* tree=parser.file_input();
    EvalVisitor visitor;
    visitor.visit(tree);
    ifs.close();
    return 0;*/

    return 0;
}