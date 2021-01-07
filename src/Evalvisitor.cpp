#include "Evalvisitor.h"

pyNamespace Namespace;

antlrcpp::Any EvalVisitor::visitFile_input(Python3Parser::File_inputContext *ctx) {
#ifdef debug_info
    printf("visitFile_input\n");
    std::cout << ctx->getText() << std::endl;
#endif
    return visitChildren(ctx);
}

antlrcpp::Any EvalVisitor::visitFuncdef(Python3Parser::FuncdefContext *ctx) {
#ifdef debug_info
    printf("visitFuncdef\n");
    std::cout << ctx->getText() << std::endl;
#endif
    return visitChildren(ctx);
}

antlrcpp::Any EvalVisitor::visitParameters(Python3Parser::ParametersContext *ctx) {
#ifdef debug_info
    printf("visitParameters\n");
    std::cout << ctx->getText() << std::endl;
#endif
    return visitChildren(ctx);
}

antlrcpp::Any EvalVisitor::visitTypedargslist(Python3Parser::TypedargslistContext *ctx) {
#ifdef debug_info
    printf("visitTypedargslist\n");
    std::cout << ctx->getText() << std::endl;
#endif
    return visitChildren(ctx);
}

antlrcpp::Any EvalVisitor::visitTfpdef(Python3Parser::TfpdefContext *ctx) {
#ifdef debug_info
    printf("visitTfpdef\n");
    std::cout << ctx->getText() << std::endl;
#endif
    return visitChildren(ctx);
}

antlrcpp::Any EvalVisitor::visitStmt(Python3Parser::StmtContext *ctx) {
#ifdef debug_info
    printf("visitStmt\n");
    std::cout << ctx->getText() << std::endl;
#endif
    return ((ctx->simple_stmt() == nullptr) ? visitCompound_stmt(ctx->compound_stmt()) : visitSimple_stmt(
            ctx->simple_stmt()));
}

antlrcpp::Any EvalVisitor::visitSimple_stmt(Python3Parser::Simple_stmtContext *ctx) {
#ifdef debug_info
    printf("visitSimple_stmt\n");
    std::cout << ctx->getText() << std::endl;
#endif
    return visitSmall_stmt(ctx->small_stmt());
}

antlrcpp::Any EvalVisitor::visitSmall_stmt(Python3Parser::Small_stmtContext *ctx) {
#ifdef debug_info
    printf("visitSmall_stmt\n");
    std::cout << ctx->getText() << std::endl;
#endif
    return ((ctx->expr_stmt() == nullptr) ? visitFlow_stmt(ctx->flow_stmt()) : visitExpr_stmt(ctx->expr_stmt()));
}

antlrcpp::Any EvalVisitor::visitExpr_stmt(Python3Parser::Expr_stmtContext *ctx) {
    //python赋值语句无返回值
#ifdef debug_info
    printf("visitExpr_stmt\n");
    std::cout << ctx->getText() << std::endl;
#endif
    //todo @@@@@@@@
    visitTestlist(ctx->testlist().back()).as<
    return visitChildren(ctx);
}

antlrcpp::Any EvalVisitor::visitAugassign(Python3Parser::AugassignContext *ctx) {
#ifdef debug_info
    printf("visitAugassign\n");
    std::cout << ctx->getText() << std::endl;
#endif
    return visitChildren(ctx);
}

antlrcpp::Any EvalVisitor::visitFlow_stmt(Python3Parser::Flow_stmtContext *ctx) {
#ifdef debug_info
    printf("visitFlow_stmt\n");
    std::cout << ctx->getText() << std::endl;
#endif
    return visitChildren(ctx);
}

antlrcpp::Any EvalVisitor::visitBreak_stmt(Python3Parser::Break_stmtContext *ctx) {
#ifdef debug_info
    printf("visitBreak_stmt\n");
    std::cout << ctx->getText() << std::endl;
#endif
    return visitChildren(ctx);
}

antlrcpp::Any EvalVisitor::visitContinue_stmt(Python3Parser::Continue_stmtContext *ctx) {
#ifdef debug_info
    printf("visitContinue_stmt\n");
    std::cout << ctx->getText() << std::endl;
#endif
    return visitChildren(ctx);
}

antlrcpp::Any EvalVisitor::visitReturn_stmt(Python3Parser::Return_stmtContext *ctx) {
#ifdef debug_info
    printf("visitReturn_stmt\n");
    std::cout << ctx->getText() << std::endl;
#endif
    return visitChildren(ctx);
}

antlrcpp::Any EvalVisitor::visitCompound_stmt(Python3Parser::Compound_stmtContext *ctx) {
#ifdef debug_info
    printf("visitCompound_stmt\n");
    std::cout << ctx->getText() << std::endl;
#endif
    return visitChildren(ctx);
}

antlrcpp::Any EvalVisitor::visitIf_stmt(Python3Parser::If_stmtContext *ctx) {
#ifdef debug_info
    printf("visitIf_stmt\n");
    std::cout << ctx->getText() << std::endl;
#endif
    return visitChildren(ctx);
}

antlrcpp::Any EvalVisitor::visitWhile_stmt(Python3Parser::While_stmtContext *ctx) {
#ifdef debug_info
    printf("visitWhile_stmt\n");
    std::cout << ctx->getText() << std::endl;
#endif
    return visitChildren(ctx);
}

antlrcpp::Any EvalVisitor::visitSuite(Python3Parser::SuiteContext *ctx) {
#ifdef debug_info
    printf("visitSuite\n");
    std::cout << ctx->getText() << std::endl;
#endif
    return visitChildren(ctx);
}

antlrcpp::Any EvalVisitor::visitTest(Python3Parser::TestContext *ctx) {
#ifdef debug_info
    printf("visitTest\n");
    std::cout << ctx->getText() << std::endl;
#endif
    return visitOr_test(ctx->or_test());
}

antlrcpp::Any EvalVisitor::visitOr_test(Python3Parser::Or_testContext *ctx) {
#ifdef debug_info
    printf("visitOr_test\n");
    std::cout << ctx->getText() << std::endl;
#endif
    auto and_test_vector = ctx->and_test();
    if (and_test_vector.empty())//此处不可能为empty
        throw pyException("Get Empty Vector of and_test()");
        //return BasicVariable();
    else if (and_test_vector.size() == 1)
        return visitAnd_test(and_test_vector.front());
    else {
        for (auto i:and_test_vector) {
            if ((visitAnd_test(i).as<BasicVariable>()).getBool())
                return BasicVariable(true);
        }
        return BasicVariable(false);
    }
}

antlrcpp::Any EvalVisitor::visitAnd_test(Python3Parser::And_testContext *ctx) {
#ifdef debug_info
    printf("visitAnd_test\n");
    std::cout << ctx->getText() << std::endl;
#endif
    auto not_test_vector = ctx->not_test();
    if (not_test_vector.empty())
        return BasicVariable();
    else if (not_test_vector.size() == 1)
        return visitNot_test(not_test_vector.front());
    else {
        for (auto i:not_test_vector) {
            if (!(visitNot_test(i).as<BasicVariable>()).getBool())
                return BasicVariable(false);
        }
        return BasicVariable(true);
    }
}

antlrcpp::Any EvalVisitor::visitNot_test(Python3Parser::Not_testContext *ctx) {
#ifdef debug_info
    printf("visitNot_test\n");
    std::cout << ctx->getText() << std::endl;
#endif
    if (ctx->not_test()) {
        return !(visitNot_test(ctx->not_test()).as<BasicVariable>().toBool());
    } else if (ctx->comparison())
        return visitComparison(ctx->comparison()).as<BasicVariable>();
    else
        throw pyException("Unexpected Error in visitNot_test()");
}

antlrcpp::Any EvalVisitor::visitComparison(Python3Parser::ComparisonContext *ctx) {
#ifdef debug_info
    printf("visitComparison\n");
    std::cout << ctx->getText() << std::endl;
#endif
    //todo 应用 comp_op_vector[i]->GREATER_THAN() 而非 getText()
    auto arith_expr_vector = ctx->arith_expr();
    auto comp_op_vector = ctx->comp_op();
    if (arith_expr_vector.size() == 1)
        return visitArith_expr(arith_expr_vector.front());
    else if (arith_expr_vector.size() > 1) {//e.g. a<b<c 从前往后(左结合)依次遍历小于号
        BasicVariable leftValue;
        BasicVariable rightValue = visitArith_expr(arith_expr_vector.front()).as<BasicVariable>();
        std::string sign;
        for (int i = 0; i < comp_op_vector.size(); ++i) {
            leftValue = rightValue;
            rightValue = visitArith_expr(arith_expr_vector[i + 1]).as<BasicVariable>();
            sign = comp_op_vector[i]->getText();
            if (sign == "<") {
                if (!(leftValue < rightValue))
                    return BasicVariable(false);
            } else if (sign == ">") {
                if (!(leftValue > rightValue))
                    return BasicVariable(false);
            } else if (sign == "==") {
                if (!(leftValue == rightValue))
                    return BasicVariable(false);
            } else if (sign == ">=") {
                if (!(leftValue >= rightValue))
                    return BasicVariable(false);
            } else if (sign == "<=") {
                if (!(leftValue <= rightValue))
                    return BasicVariable(false);
            } else if (sign == "!=") {
                if (!(leftValue != rightValue))
                    return BasicVariable(false);
            } else throw pyException("Unexpected Error1 in visitComparison()");
        }
        return BasicVariable(true);
    } else throw pyException("Unexpected Error2 in visitComparison()");
}

antlrcpp::Any EvalVisitor::visitComp_op(Python3Parser::Comp_opContext *ctx) {
#ifdef debug_info
    printf("visitComp_op\n");
    std::cout << ctx->getText() << std::endl;
#endif
    return nullptr;
    //return visitChildren(ctx);
}

antlrcpp::Any EvalVisitor::visitArith_expr(Python3Parser::Arith_exprContext *ctx) {
#ifdef debug_info
    printf("visitArith_expr\n");
    std::cout << ctx->getText() << std::endl;
#endif
    auto term_vector = ctx->term();
    auto addorsub_op_vector = ctx->addorsub_op();
    if (term_vector.size() == 1)
        return visitTerm(term_vector.front());
    else if (term_vector.size() > 1) {//e.g. a+b-c 从前往后(左结合)依次遍历加减号
        BasicVariable leftValue = visitTerm(term_vector.front()).as<BasicVariable>();
        BasicVariable rightValue;
        std::string sign;
        for (int i = 0; i < addorsub_op_vector.size(); ++i) {
            rightValue = visitTerm(term_vector[i + 1]).as<BasicVariable>();
            sign = addorsub_op_vector[i]->getText();
            if (sign == "+") {
                leftValue += rightValue;
            } else if (sign == "-") {
                leftValue -= rightValue;
            } else throw pyException("Unexpected Error1 in visitArith_expr()");
        }
        return leftValue;
    } else throw pyException("Unexpected Error2 in visitArith_expr()");
}

antlrcpp::Any EvalVisitor::visitAddorsub_op(Python3Parser::Addorsub_opContext *ctx) {
#ifdef debug_info
    printf("visitAddorsub_op\n");
    std::cout << ctx->getText() << std::endl;
#endif
    return nullptr;
    //return visitChildren(ctx);
}

antlrcpp::Any EvalVisitor::visitTerm(Python3Parser::TermContext *ctx) {
#ifdef debug_info
    printf("visitTerm\n");
    std::cout << ctx->getText() << std::endl;
#endif
    auto factor_vector = ctx->factor();
    auto muldivmod_op = ctx->muldivmod_op();
    if (factor_vector.size() == 1)
        return visitFactor(factor_vector.front());
    else if (factor_vector.size() > 1) {//e.g. a*b/c 从前往后(左结合)依次遍历符号
        BasicVariable leftValue = visitFactor(factor_vector.front()).as<BasicVariable>();
        BasicVariable rightValue;
        std::string sign;
        for (int i = 0; i < muldivmod_op.size(); ++i) {
            rightValue = visitFactor(factor_vector[i + 1]).as<BasicVariable>();
            sign = muldivmod_op[i]->getText();
            if (sign == "*") {
                leftValue *= rightValue;
            } else if (sign == "/") {
                leftValue /= rightValue;//todo 此处相关函数待实现
            } else if (sign == "//") {
                leftValue /= rightValue;
            } else if (sign == "%") {
                leftValue %= rightValue;
            } else throw pyException("Unexpected Error1 in visitTerm()");
        }
        return leftValue;
    } else throw pyException("Unexpected Error2 in visitTerm()");
}

antlrcpp::Any EvalVisitor::visitMuldivmod_op(Python3Parser::Muldivmod_opContext *ctx) {
#ifdef debug_info
    printf("visitMuldivmod_op\n");
    std::cout << ctx->getText() << std::endl;
#endif
    return nullptr;
    //return visitChildren(ctx);
}

antlrcpp::Any EvalVisitor::visitFactor(Python3Parser::FactorContext *ctx) {
    //  此处可以修改g4文件
    //  将    factor: ('+'|'-') factor | atom_expr;
    //  改为  factor: addorsub_op factor | atom_expr;
    //  并下调 addorsub_op: '+'|'-'; 行位置
    //  但是需要调整Python3Parser.h/.cpp中内容
#ifdef debug_info
    printf("visitFactor\n");
    std::cout << ctx->getText() << std::endl;
#endif
    if (ctx->factor()) {
        if (ctx->ADD())
            return +(visit(ctx->factor()).as<BasicVariable>());
        else if (ctx->MINUS())
            return -(visit(ctx->factor()).as<BasicVariable>());
    } else if (ctx->atom_expr()) {
        return visit(ctx->atom_expr());
    } else throw pyException("Unexpected Error in visitFactor()");
}

antlrcpp::Any EvalVisitor::visitAtom_expr(Python3Parser::Atom_exprContext *ctx) {
#ifdef debug_info
    printf("visitAtom_expr\n");
    std::cout << ctx->getText() << std::endl;
#endif
    if (!ctx->trailer()) return visitAtom(ctx->atom());
        //非函数则直接返回Atom（BasicVariable），可以是pyName类型的BasicVariable
    else {
        BasicVariable atom = visitAtom(ctx->atom());
        std::vector<std::pair<BasicVariable, BasicVariable> > arglist_vector = visitTrailer(ctx->trailer());
        //if (atom.getType() != BasicVariable::pyName)
        //    throw pyException("Atom for Function Name is not pyName Type BasicVariable");

        if (atom.getName() == "print") {
            if (!arglist_vector.empty()) {
                for (auto i = arglist_vector.begin(); i != arglist_vector.end() - 1; ++i)
                    if (i->first.isNull()) {
                        std::cout << Namespace.getVariable(i->second.getName()) << ' ';
                    } else throw pyException("Call print() with Keyword Argument");
                std::cout << Namespace.getVariable(arglist_vector.back().second.getName()) << std::endl;
            } else std::cout << std::endl;
            return BasicVariable();
        } else if (atom.getName() == "bool") {
            if(arglist_vector.empty())
                return BasicVariable(false);
            else if(arglist_vector.size()==1){
                BasicVariable temp(arglist_vector.front().second);
                return temp.toBool();
            }else throw pyException("bool() Get more than 1 Argument");
        } else if (atom.getName() == "int") {

        } else if (atom.getName() == "float") {

        } else if (atom.getName() == "str") {

        } else {
            Namespace.getFunction(atom.getName());

            if (ctx->trailer()->arglist() != nullptr) {
                bool positionalArgument = true;
                //positional arg,即为c++函数参数表中内容,不可出现在keyword arg后
                //keyword arg,形如"Name = Value"代表指定参数的参数值
                for (auto i:ctx->trailer()->arglist()->argument()) {
                    if (positionalArgument) {
                        if (i->test().size() == 2)
                            positionalArgument = false;
                    } else if (i->test().size() == 1)
                        throw pyException("Function Positional Argument Follow Keyword Argument");

                    if (i->test().size() == 1) {

                    } else {//i->test().size() == 2

                    }
                    tret = visitTest(ctx->trailer()->arglist()->argument()[i]->test()[0]);
                    if (!tret.is<std::vector<dtype> >()) continue;
                    std::vector<dtype> tmp = tret.as<std::vector<dtype> >();
                    for (auto x : tmp) ret.push_back(x);
                }
            }
            return new BasicVariable();
        }
    }
    return visitChildren(ctx);
}

antlrcpp::Any EvalVisitor::visitTrailer(Python3Parser::TrailerContext *ctx)
//return type: std::vector<std::pair<BasicVariable, BasicVariable> >
{
#ifdef debug_info
    printf("visitTrailer\n");
    std::cout << ctx->getText() << std::endl;
#endif
    if (ctx->arglist())
        return visitArglist(ctx->arglist());
    else std::vector<std::pair<BasicVariable, BasicVariable> >();
    return visitChildren(ctx);//to arglist
}

antlrcpp::Any EvalVisitor::visitAtom(Python3Parser::AtomContext *ctx) {
#ifdef debug_info
    printf("visitAtom\n");
    std::cout << ctx->getText() << std::endl;
#endif
    if (ctx->NAME())
        return BasicVariable(ctx->NAME()->getText(), BasicVariable::setName);
    else if (ctx->NUMBER()) {
        if (ctx->NUMBER()->getText().find('.') == std::string::npos)//保存getText()优化
            return BasicVariable(HighPrecision(ctx->getText()));
        else return BasicVariable(stod(ctx->NUMBER()->getText()));//todo 此处stod
    } else if (!ctx->STRING().empty()) {
        BasicVariable temps("");
        for (auto i : ctx->STRING())
            temps += BasicVariable(i->getText().substr(1, i->getText().length() - 2));//todo 字符串首末有双引号
        return temps;
    } else if (ctx->NONE())
        return BasicVariable(BasicVariable::setNone);
    else if (ctx->TRUE())
        return BasicVariable(true);
    else if (ctx->FALSE())
        return BasicVariable(false);
    else if (ctx->test())
        return visitTest(ctx->test());
    else throw pyException("Unexpected Error in visitAtom()");
}

antlrcpp::Any EvalVisitor::visitTestlist(Python3Parser::TestlistContext *ctx) {
#ifdef debug_info
    printf("visitTestlist\n");
    std::cout << ctx->getText() << std::endl;
#endif
    return visitChildren(ctx);
}

antlrcpp::Any EvalVisitor::visitArglist(Python3Parser::ArglistContext *ctx) {
#ifdef debug_info
    printf("visitArglist\n");
    std::cout << ctx->getText() << std::endl;
#endif
    std::vector<std::pair<BasicVariable, BasicVariable> > arglist;
    auto argument_vector = ctx->argument();
    for (auto i:argument_vector)
        arglist.emplace_back(visitArgument(i));
    return arglist;
}

antlrcpp::Any EvalVisitor::visitArgument(Python3Parser::ArgumentContext *ctx) {
#ifdef debug_info
    printf("visitArgument\n");
    std::cout << ctx->getText() << std::endl;
#endif
    auto test_vector = ctx->test();
    if (test_vector.size() == 1)
        return std::make_pair(BasicVariable(), visitTest(ctx->test().front()).as<BasicVariable>());
    else if (test_vector.size() == 2)
        return std::make_pair(visitTest(ctx->test()[0]).as<BasicVariable>(),
                              visitTest(ctx->test()[1]).as<BasicVariable>());
    else throw pyException("Argument with 0 or more than 2 Test");
}
