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
    //const auto &parameters = visitParameters(ctx->parameters()).as<pyNamespace::parameterVector>();
    Namespace.defineFunction(ctx->NAME()->getText(), ctx->suite(),
                             visitParameters(ctx->parameters()).as<pyNamespace::parameterVector>());
    return nullptr;
}

antlrcpp::Any EvalVisitor::visitParameters(Python3Parser::ParametersContext *ctx) {
#ifdef debug_info
    printf("visitParameters\n");
    std::cout << ctx->getText() << std::endl;
#endif
    if (ctx->typedargslist())
        return visitTypedargslist(ctx->typedargslist());
    else return pyNamespace::parameterVector();
}

antlrcpp::Any EvalVisitor::visitTypedargslist(Python3Parser::TypedargslistContext *ctx) {
#ifdef debug_info
    printf("visitTypedargslist\n");
    std::cout << ctx->getText() << std::endl;
#endif
    const auto &tfpdefVector = ctx->tfpdef();
    const auto &testVector = ctx->test();
    pyNamespace::parameterVector parameters;
    // 有默认值的变量必在最后
    const auto tfpdefNumber = tfpdefVector.size();
    const auto testNumber = testVector.size();
    for (int i = 0, boundary = tfpdefNumber - testNumber; i < boundary; ++i)
        parameters.emplace_back(std::make_pair(tfpdefVector[i]->NAME()->getText(), BasicVariable()));
    for (int i = 0, boundary = testNumber; i < boundary; ++i)
        parameters.emplace_back(std::make_pair(
                tfpdefVector[tfpdefNumber - testNumber + i]->NAME()->getText(), BasicVariable()));
    return parameters;
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
    return (ctx->simple_stmt() ?
            visitSimple_stmt(ctx->simple_stmt()) :
            visitCompound_stmt(ctx->compound_stmt()));
}

antlrcpp::Any EvalVisitor::visitSimple_stmt(Python3Parser::Simple_stmtContext *ctx) {
#ifdef debug_info
    printf("visitSimple_stmt\n");
    std::cout << ctx->getText() << std::endl;
#endif
    //simple_stmt: small_stmt  NEWLINE;
    return visitSmall_stmt(ctx->small_stmt());
}

antlrcpp::Any EvalVisitor::visitSmall_stmt(Python3Parser::Small_stmtContext *ctx) {
#ifdef debug_info
    printf("visitSmall_stmt\n");
    std::cout << ctx->getText() << std::endl;
#endif
    return (ctx->expr_stmt() ? visitExpr_stmt(ctx->expr_stmt()) : visitFlow_stmt(ctx->flow_stmt()));
}

antlrcpp::Any EvalVisitor::visitExpr_stmt(Python3Parser::Expr_stmtContext *ctx) {
    //python赋值语句无返回值
#ifdef debug_info
    printf("visitExpr_stmt\n");
    std::cout << ctx->getText() << std::endl;
#endif
    //pyName会自atom直接至本函数
    /*if(ctx->augassign()){//e.g. += /=

    }else if(ctx->ASSIGN().front().)
    antlrcpp::Any tempPtr = ctx->testlist()
    antlrcpp::Any tempPtr = ctx->or_test();
    //antlrcpp::Any tempPtr = ctx->or_test()->and_test(0)->not_test(0)->comparison();
    if (tempPtr.isNotNull()) {
        tempPtr = tempPtr.as<Python3Parser::ComparisonContext *>()
                ->arith_expr(0)->term(0)->factor(0)->atom_expr();
        if(tempPtr.isNotNull()){
            tempPtr = tempPtr.as<Python3Parser::Atom_exprContext*>()
                    ->atom();
        }
    }
    if ()
    visitTestlist(ctx->testlist().front().);

    //visitTestlist(ctx->testlist().back()).as<
    //return visitChildren(ctx);*/
    //todo 不知道怎么提前判断左值
    // 可以考虑 BasicVaribal 加一 flag 用于保护 pyName 不被转为实值

    std::vector<std::vector<BasicVariable> > testlistVector;
    for (auto i:ctx->testlist())
        testlistVector.emplace_back(visitTestlist(i).as<std::vector<BasicVariable> >());

    if (ctx->augassign()) {
        if (testlistVector.size() != 2)
            throw pyException("Unexpected Error1 in visitExpr_stmt()");
        const auto &leftTestlist = testlistVector.front();
        const auto &rightTestlist = testlistVector.back();
        if (leftTestlist.size() != 1 || rightTestlist.size() != 1)
            throw pyException("Unexpected Error2 in visitExpr_stmt()");

        const auto &leftName = leftTestlist.front().getName();
        const auto &leftValue = Namespace.getValue(leftTestlist.front());
        const auto &rightValue = Namespace.getValue(rightTestlist.front());

        if (ctx->augassign()->ADD_ASSIGN())
            Namespace.assignVariable(leftName, leftValue + rightValue, pyNamespace::pyNotDeclare);
        else if (ctx->augassign()->SUB_ASSIGN())
            Namespace.assignVariable(leftName, leftValue - rightValue, pyNamespace::pyNotDeclare);
        else if (ctx->augassign()->MULT_ASSIGN())
            Namespace.assignVariable(leftName, leftValue * rightValue, pyNamespace::pyNotDeclare);
        else if (ctx->augassign()->DIV_ASSIGN())
            Namespace.assignVariable(leftName, leftValue / rightValue, pyNamespace::pyNotDeclare);
        else if (ctx->augassign()->IDIV_ASSIGN())
            Namespace.assignVariable(leftName, leftValue.evenlyDivide(rightValue), pyNamespace::pyNotDeclare);
        else if (ctx->augassign()->MOD_ASSIGN())
            Namespace.assignVariable(leftName, leftValue % rightValue, pyNamespace::pyNotDeclare);

    } else {
        if (testlistVector.size() < 2) {
            // throw pyException("Unexpected Error3 in visitExpr_stmt()");
            // DO NOTHING
            // 函数开头已经visit过了
            return nullptr;
        } else {
            auto leftTestlist = testlistVector.end() - 1;
            auto rightTestlist = testlistVector.end();
            for (int i = testlistVector.size() - 2; i >= 0; --i) {
                rightTestlist--;
                leftTestlist--;
                if (leftTestlist->size() != rightTestlist->size())
                    throw pyException("Different Number of Values on Two Sides of Expression Statement");
                for (int j = 0; j < leftTestlist->size(); ++j) {
                    Namespace.assignVariable((*leftTestlist)[j].getName(),
                                             Namespace.getValue((*rightTestlist)[j]),
                                             pyNamespace::pyGlobal);//todo global/local判断待研究
                }
            }
        }
    }
    return nullptr;
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
    if (ctx->break_stmt())
        return pyFlow(pyFlow::pyBreak);
    else if (ctx->continue_stmt())
        return pyFlow(pyFlow::pyContinue);
    else if (ctx->return_stmt())
        return visitReturn_stmt(ctx->return_stmt());
    else throw pyException("Unexpected Error in visitFlow_stmt()");
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
    if (ctx->testlist())
        return visitTestlist(ctx->testlist());
    else return BasicVariable(BasicVariable::setNone);
}

antlrcpp::Any EvalVisitor::visitCompound_stmt(Python3Parser::Compound_stmtContext *ctx) {
#ifdef debug_info
    printf("visitCompound_stmt\n");
    std::cout << ctx->getText() << std::endl;
#endif
    if (ctx->if_stmt())
        return visitIf_stmt(ctx->if_stmt());
    else if (ctx->while_stmt())
        return visitWhile_stmt(ctx->while_stmt());
    else if (ctx->funcdef())
        return visitFuncdef(ctx->funcdef());
    else throw pyException("Unexpected error in visitCompound_stmt()");
}

antlrcpp::Any EvalVisitor::visitIf_stmt(Python3Parser::If_stmtContext *ctx) {
#ifdef debug_info
    printf("visitIf_stmt\n");
    std::cout << ctx->getText() << std::endl;
#endif
    const auto &testVector = ctx->test();
    const auto &suiteVector = ctx->suite();
    for (int i = 0; i < testVector.size(); ++i) {
        if (visitTest(testVector[i]).as<BasicVariable>().getBool())
            return visitSuite(suiteVector[i]);
        else break;
    }
    if (ctx->ELSE()) return visitSuite(suiteVector.back());
    throw pyException("Unexpected Error in visitIf_stmt()");
}

antlrcpp::Any EvalVisitor::visitWhile_stmt(Python3Parser::While_stmtContext *ctx) {
#ifdef debug_info
    printf("visitWhile_stmt\n");
    std::cout << ctx->getText() << std::endl;
#endif
    antlrcpp::Any suiteReturn;
    while (visitTest(ctx->test()).as<BasicVariable>().getBool()) {
        suiteReturn = visitSuite(ctx->suite());
        if (suiteReturn.is<pyFlow>()) {
            const auto &ret = suiteReturn.as<pyFlow>();
            if (ret.getType() == pyFlow::pyContinue) continue;
            else if (ret.getType() == pyFlow::pyBreak) break;
            else if (ret.getType() == pyFlow::pyReturn)
                return ret;
        } else throw pyException("Unexpected Suite Return in visitWhile_stmt()");
    }
    return nullptr;
}

antlrcpp::Any EvalVisitor::visitSuite(Python3Parser::SuiteContext *ctx) {
#ifdef debug_info
    printf("visitSuite\n");
    std::cout << ctx->getText() << std::endl;
#endif
    if (ctx->simple_stmt())
        return visitSimple_stmt(ctx->simple_stmt());
    else {// NEWLINE INDENT stmt+ DEDENT
        const auto &stmtVector = ctx->stmt();
        for (auto i:stmtVector) {
            const antlrcpp::Any &stmtReturn = visitStmt(i);
            if (stmtReturn.is<pyFlow>())
                return stmtReturn.as<pyFlow>();
            else throw pyException("Unexpected Suite Return");
        }
    }
    return nullptr;
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
    const auto &and_test_vector = ctx->and_test();
    if (and_test_vector.empty())//此处不可能为empty
        throw pyException("Get Empty Vector of and_test()");
        //return BasicVariable();
    else if (and_test_vector.size() == 1)
        return visitAnd_test(and_test_vector.front());
    else {
        for (auto i:and_test_vector) {
            if ((Namespace.getValue(visitAnd_test(i).as<BasicVariable>())).getBool())
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
    const auto &not_test_vector = ctx->not_test();
    if (not_test_vector.empty())
        return BasicVariable();
    else if (not_test_vector.size() == 1)
        return visitNot_test(not_test_vector.front());
    else {
        for (auto i:not_test_vector) {
            if (!(Namespace.getValue(visitNot_test(i).as<BasicVariable>())).getBool())
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
        return !((Namespace.getValue(visitNot_test(ctx->not_test()).as<BasicVariable>())).toBool());
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
    //应用 comp_op_vector[i]->GREATER_THAN() 而非 getText()
    const auto &arith_expr_vector = ctx->arith_expr();
    const auto &comp_op_vector = ctx->comp_op();
    if (arith_expr_vector.size() == 1)
        return visitArith_expr(arith_expr_vector.front());
    else if (arith_expr_vector.size() > 1) {//e.g. a<b<c 从前往后(左结合)依次遍历小于号
        BasicVariable leftValue;
        BasicVariable rightValue = Namespace.getValue(visitArith_expr(arith_expr_vector.front()).as<BasicVariable>());
        std::string sign;
        for (int i = 0; i < comp_op_vector.size(); ++i) {
            leftValue = rightValue;
            rightValue = Namespace.getValue(visitArith_expr(arith_expr_vector[i + 1]).as<BasicVariable>());
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
    const auto &term_vector = ctx->term();
    const auto &addorsub_op_vector = ctx->addorsub_op();
    if (term_vector.size() == 1)
        return visitTerm(term_vector.front());
    else if (term_vector.size() > 1) {//e.g. a+b-c 从前往后(左结合)依次遍历加减号
        BasicVariable leftValue = Namespace.getValue(visitTerm(term_vector.front()).as<BasicVariable>());
        BasicVariable rightValue;
        std::string sign;
        for (int i = 0; i < addorsub_op_vector.size(); ++i) {
            rightValue = Namespace.getValue(visitTerm(term_vector[i + 1]).as<BasicVariable>());
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
    const auto &factor_vector = ctx->factor();
    const auto &muldivmod_op = ctx->muldivmod_op();
    if (factor_vector.size() == 1)
        return visitFactor(factor_vector.front());
    else if (factor_vector.size() > 1) {
        //e.g. a*b/c 从前往后(左结合)依次遍历符号
        //并将pyName转为实值
        BasicVariable leftValue = Namespace.getValue(visitFactor(factor_vector.front()).as<BasicVariable>());
        BasicVariable rightValue;
        std::string sign;
        for (int i = 0; i < muldivmod_op.size(); ++i) {
            rightValue = Namespace.getValue(visitFactor(factor_vector[i + 1]).as<BasicVariable>());
            sign = muldivmod_op[i]->getText();
            if (sign == "*") {
                leftValue *= rightValue;
            } else if (sign == "/") {
                leftValue /= rightValue;
            } else if (sign == "//") {
                leftValue.evenlyDivide(rightValue);
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
            return +Namespace.getValue(visitFactor(ctx->factor()).as<BasicVariable>());
        else if (ctx->MINUS())
            return -Namespace.getValue(visitFactor(ctx->factor()).as<BasicVariable>());
    } else if (ctx->atom_expr()) {
        return visitAtom_expr(ctx->atom_expr());
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
        const auto tempAtom(visitAtom(ctx->atom()).as<BasicVariable>());
        std::vector<std::pair<BasicVariable, BasicVariable> > arglist_vector = visitTrailer(ctx->trailer());
        //if (tempAtom.getType() != BasicVariable::pyName)
        //    throw pyException("Atom for Function Name is not pyName Type BasicVariable");

        if (tempAtom.getName() == "print") {
            if (!arglist_vector.empty()) {
                for (auto i = arglist_vector.begin(); i != arglist_vector.end() - 1; ++i)
                    if (i->first.isNull()) {
                        std::cout << Namespace.getValue(i->second) << ' ';
                    } else throw pyException("Call print() with Keyword Argument");
                std::cout << Namespace.getValue(arglist_vector.back().second) << std::endl;
            } else std::cout << std::endl;
            return BasicVariable();

        } else if (tempAtom.getName() == "bool") {
            if (arglist_vector.empty())
                return BasicVariable(false);
            else if (arglist_vector.size() == 1) {
                BasicVariable temp(Namespace.getValue(arglist_vector.front().second));
                return temp.toBool();
            } else throw pyException("bool() Get more than 1 Argument");

        } else if (tempAtom.getName() == "int") {
            if (arglist_vector.empty())
                return BasicVariable(HighPrecision(0));
            else if (arglist_vector.size() == 1) {
                BasicVariable temp(Namespace.getValue(arglist_vector.front().second));
                return temp.toInt();
            } else throw pyException("int() Get more than 1 Argument");
            //事实上int("101",2);代表将字符串转为二进制的值

        } else if (tempAtom.getName() == "float") {
            if (arglist_vector.empty())
                return BasicVariable(0.0);
            else if (arglist_vector.size() == 1) {
                BasicVariable temp(Namespace.getValue(arglist_vector.front().second));
                return temp.toFloat();
            } else throw pyException("float() Get more than 1 Argument");

        } else if (tempAtom.getName() == "str") {
            if (arglist_vector.empty())
                return BasicVariable("");
            else if (arglist_vector.size() == 1) {
                BasicVariable temp(Namespace.getValue(arglist_vector.front().second));
                return temp.toStr();
            } else throw pyException("str() Get more than 1 Argument");


        } else {
            Namespace.getFunction(tempAtom.getName());
            /*
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
            }*/
            return BasicVariable();
        }
    }
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
    if (ctx->NAME()) {
        BasicVariable temp(ctx->NAME()->getText(), BasicVariable::setName);
        return temp;
        //return BasicVariable(ctx->NAME()->getText(), BasicVariable::setName);
    } else if (ctx->NUMBER()) {
        if (ctx->NUMBER()->getText().find('.') == std::string::npos)//保存getText()优化
            return BasicVariable(HighPrecision(ctx->getText()));
        else return BasicVariable(stod(ctx->NUMBER()->getText()));//todo 此处stod
    } else if (!ctx->STRING().empty()) {
        BasicVariable temps("");
        for (auto i : ctx->STRING())// 字符串首末有单/双引号且可以连续出现
            temps += BasicVariable(i->getText().substr(1, i->getText().length() - 2));
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

antlrcpp::Any EvalVisitor::visitTestlist(Python3Parser::TestlistContext *ctx)
//return std::vector<BasicVariable>
{
#ifdef debug_info
    printf("visitTestlist\n");
    std::cout << ctx->getText() << std::endl;
#endif
    auto testVector = ctx->test();
    antlrcpp::Any testReturn;
    std::vector<BasicVariable> retVector;
    for (auto i:testVector) {
        testReturn = visitTest(i);
        if (testReturn.is<BasicVariable>())
            retVector.emplace_back(testReturn.as<BasicVariable>());
            //todo 若test是个testlist，则等价于多个test
        else if (testReturn.is<std::vector<BasicVariable> >()) {
            const std::vector<BasicVariable> &testReturnVector
                    = testReturn.as<std::vector<BasicVariable> >();
            for (const auto &j:testReturnVector)
                retVector.emplace_back(j);
        }
    }
    return retVector;
}

antlrcpp::Any EvalVisitor::visitArglist(Python3Parser::ArglistContext *ctx) {
#ifdef debug_info
    printf("visitArglist\n");
    std::cout << ctx->getText() << std::endl;
#endif
    std::vector<std::pair<BasicVariable, BasicVariable> > arglist;
    const auto &argument_vector = ctx->argument();
    for (auto i:argument_vector)
        arglist.emplace_back(visitArgument(i));
    return arglist;
}

antlrcpp::Any EvalVisitor::visitArgument(Python3Parser::ArgumentContext *ctx) {
#ifdef debug_info
    printf("visitArgument\n");
    std::cout << ctx->getText() << std::endl;
#endif
    const auto &test_vector = ctx->test();
    if (test_vector.size() == 1)
        return std::make_pair(BasicVariable(), visitTest(test_vector.front()).as<BasicVariable>());
    else if (test_vector.size() == 2)
        return std::make_pair(visitTest(test_vector.front()).as<BasicVariable>(),
                              visitTest(test_vector.back()).as<BasicVariable>());
    else throw pyException("Argument with 0 or more than 2 Test");
}
