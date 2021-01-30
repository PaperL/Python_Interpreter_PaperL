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
                             visitParameters(ctx->parameters()).as<pyNamespace::variableVector>());
    return nullptr;
}

antlrcpp::Any EvalVisitor::visitParameters(Python3Parser::ParametersContext *ctx) {
#ifdef debug_info
    printf("visitParameters\n");
    std::cout << ctx->getText() << std::endl;
#endif
    if (ctx->typedargslist())
        return visitTypedargslist(ctx->typedargslist());
    else return pyNamespace::variableVector();
}

antlrcpp::Any EvalVisitor::visitTypedargslist(Python3Parser::TypedargslistContext *ctx) {
#ifdef debug_info
    printf("visitTypedargslist\n");
    std::cout << ctx->getText() << std::endl;
#endif
    const auto &tfpdefVector = ctx->tfpdef();
    const auto &testVector = ctx->test();
    pyNamespace::variableVector parameters;
    // 有默认值的变量必在最后
    const auto tfpdefNumber = tfpdefVector.size();
    const auto testNumber = testVector.size();
    //std::cout << "num: " << tfpdefNumber << ", " << testNumber << std::endl;
    for (int i = 0, boundary = tfpdefNumber - testNumber; i < boundary; ++i)
        parameters.emplace_back(std::make_pair(tfpdefVector[i]->NAME()->getText(), BasicVariable()));
    for (int i = 0, boundary = testNumber; i < boundary; ++i)
        parameters.emplace_back(std::make_pair(
                tfpdefVector[tfpdefNumber - testNumber + i]->NAME()->getText(),
                visitTest(testVector[i]).as<BasicVariable>()));
    return parameters;
}

antlrcpp::Any EvalVisitor::visitTfpdef(Python3Parser::TfpdefContext *ctx) {
#ifdef debug_info
    printf("visitTfpdef\n");
    std::cout << ctx->getText() << std::endl;
#endif
    return nullptr;
    //return visitChildren(ctx);
}

antlrcpp::Any EvalVisitor::visitStmt(Python3Parser::StmtContext *ctx) {
#ifdef debug_info
    printf("visitStmt\n");
    std::cout << ctx->getText() << std::endl;
#endif
    //std::cout << "# " << ctx->getText() << std::endl;
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
    std::vector<pyNamespace::valueVector> testlistVector;
    for (auto i:ctx->testlist())
        testlistVector.emplace_back(visitTestlist(i).as<pyNamespace::valueVector>());

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
                                             pyNamespace::pyLocal);//todo global/local判断待研究
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
    return nullptr;
    //return visitChildren(ctx);
}

antlrcpp::Any EvalVisitor::visitFlow_stmt(Python3Parser::Flow_stmtContext *ctx) {
#ifdef debug_info
    printf("visitFlow_stmt\n");
    std::cout << ctx->getText() << std::endl;
#endif
    if (ctx->break_stmt())
        return visitBreak_stmt(ctx->break_stmt());
    else if (ctx->continue_stmt())
        return visitContinue_stmt(ctx->continue_stmt());
    else if (ctx->return_stmt())
        return visitReturn_stmt(ctx->return_stmt());
    else throw pyException("Unexpected Error in visitFlow_stmt()");
}

antlrcpp::Any EvalVisitor::visitBreak_stmt(Python3Parser::Break_stmtContext *ctx) {
#ifdef debug_info
    printf("visitBreak_stmt\n");
    std::cout << ctx->getText() << std::endl;
#endif
    return pyFlow(pyFlow::pyBreak);
    //return visitChildren(ctx);
}

antlrcpp::Any EvalVisitor::visitContinue_stmt(Python3Parser::Continue_stmtContext *ctx) {
#ifdef debug_info
    printf("visitContinue_stmt\n");
    std::cout << ctx->getText() << std::endl;
#endif
    return pyFlow(pyFlow::pyContinue);
    //return visitChildren(ctx);
}

antlrcpp::Any EvalVisitor::visitReturn_stmt(Python3Parser::Return_stmtContext *ctx) {
#ifdef debug_info
    printf("visitReturn_stmt\n");
    std::cout << ctx->getText() << std::endl;
#endif
    if (ctx->testlist()) {
        // 此处需要将 testlist 中内容均由 pyName 转为实际值
        auto testlistReturn = visitTestlist(ctx->testlist()).as<pyNamespace::valueVector>();
        pyNamespace::valueVector testlistValue;
        for (auto i:testlistReturn)
            testlistValue.emplace_back(Namespace.getValue(i));
        return pyFlow(pyFlow::pyReturn, testlistValue);
    } else return pyFlow(pyFlow::pyReturn);
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
        auto testReturn = visitTest(testVector[i]).as<BasicVariable>();
        testReturn = Namespace.getValue(testReturn).toBool();
        if (testReturn.getBool()) return visitSuite(suiteVector[i]);
    }
    if (ctx->ELSE()) return visitSuite(suiteVector.back());
    return nullptr;
    //throw pyException("Unexpected Error in visitIf_stmt()");
}

antlrcpp::Any EvalVisitor::visitWhile_stmt(Python3Parser::While_stmtContext *ctx) {
#ifdef debug_info
    printf("visitWhile_stmt\n");
    std::cout << ctx->getText() << std::endl;
#endif
    antlrcpp::Any suiteReturn;
    auto testReturn = visitTest(ctx->test()).as<BasicVariable>();
    testReturn = Namespace.getValue(testReturn).toBool();
    while (testReturn.getBool()) {
        suiteReturn = visitSuite(ctx->suite());
        if (suiteReturn.is<pyFlow>()) {
            const auto &ret = suiteReturn.as<pyFlow>();
            if (ret.getType() == pyFlow::pyContinue) continue;
            else if (ret.getType() == pyFlow::pyBreak) break;
            else if (ret.getType() == pyFlow::pyReturn) return ret;
        }// else throw pyException("Unexpected Suite Return in visitWhile_stmt()");
        testReturn = visitTest(ctx->test()).as<BasicVariable>();
        testReturn = Namespace.getValue(testReturn).toBool();
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
            const antlrcpp::Any stmtReturn = visitStmt(i);
            if (stmtReturn.is<pyFlow>()) return stmtReturn;
            //else throw pyException("Unexpected Suite Return");
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
    if (and_test_vector.size() == 1)
        return visitAnd_test(and_test_vector.front());
    else {
        for (auto i:and_test_vector) {
            auto andTestReturn = visitAnd_test(i).as<BasicVariable>();
            andTestReturn = Namespace.getValue(andTestReturn).toBool();
            if (andTestReturn.getBool()) return BasicVariable(true);
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
    if (not_test_vector.size() == 1)
        return visitNot_test(not_test_vector.front());
    else {
        for (auto i:not_test_vector) {
            auto notTestReturn = visitNot_test(i).as<BasicVariable>();
            notTestReturn = Namespace.getValue(notTestReturn).toBool();
            if (!notTestReturn.getBool()) return BasicVariable(false);
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
        return visitComparison(ctx->comparison());
    else throw pyException("Unexpected Error in visitNot_test()");
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
            const auto &sign = muldivmod_op[i];
            if (sign->STAR())
                leftValue *= rightValue;
            else if (sign->DIV())
                leftValue /= rightValue;
            else if (sign->IDIV())
                leftValue.enenlyDivideEqual(rightValue);
            else if (sign->MOD())
                leftValue %= rightValue;
            else throw pyException("Unexpected Error1 in visitTerm()");
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
    //非函数则直接返回BasicVariable Atom，可以是pyName类型的BasicVariable
    if (!ctx->trailer()) return visitAtom(ctx->atom());
    else {
        const auto funcName = visitAtom(ctx->atom()).as<BasicVariable>().getName();
        const auto argVector = visitTrailer(ctx->trailer()).as<pyNamespace::variableVector>();
        //todo argVector 使用 const 引用 内容会变为随机数，原因不明
        //if (tempAtom.getType() != BasicVariable::pyName)
        //    throw pyException("Atom for Function Name is not pyName Type BasicVariable");
        if (funcName == "print") {
            if (!argVector.empty()) {
                for (auto i = argVector.begin(); i != argVector.end() - 1; ++i)
                    std::cout << Namespace.getValue(i->second) << ' ';
                //throw pyException("Call print() with Keyword Argument");
                std::cout << Namespace.getValue(argVector.back().second) << std::endl;
            } else std::cout << std::endl;
            return BasicVariable(BasicVariable::setNone);// pyNull

        } else if (funcName == "bool") {
            if (argVector.empty())
                return BasicVariable(false);
            else if (argVector.size() == 1) {
                BasicVariable temp = Namespace.getValue(argVector.front().second);
                return temp.toBool();
            } else throw pyException("bool() Get more than 1 Argument");

        } else if (funcName == "int") {
            if (argVector.empty())
                return BasicVariable(HighPrecision(0));
            else if (argVector.size() == 1) {
                BasicVariable temp = Namespace.getValue(argVector.front().second);
                return temp.toInt();
            } else throw pyException("int() Get more than 1 Argument");
            // 事实上int("101",2);代表将字符串转为二进制的值

        } else if (funcName == "float") {
            if (argVector.empty())
                return BasicVariable(0.0);
            else if (argVector.size() == 1) {
                BasicVariable temp = Namespace.getValue(argVector.front().second);
                return temp.toFloat();
            } else throw pyException("float() Get more than 1 Argument");

        } else if (funcName == "str") {
            if (argVector.empty())
                return BasicVariable((std::string()));
            else if (argVector.size() == 1) {
                BasicVariable temp = Namespace.getValue(argVector.front().second);
                return temp.toStr();
            } else throw pyException("str() Get more than 1 Argument");

        } else {
            // 执行函数
            const auto suiteCtx = Namespace.loadFunction(funcName, argVector);
            const antlrcpp::Any suiteReturn = visitSuite(suiteCtx);

            pyNamespace::valueVector ret;
            if (suiteReturn.is<pyFlow>()) {
                if (suiteReturn.as<pyFlow>().getType() == pyFlow::pyReturn)
                    ret = suiteReturn.as<pyFlow>().getReturnValue();
                else throw pyException("Function Stop Because Continue/Break");
            }// else throw pyException("Function Return is not pyFlow");

            Namespace.unloadFunction();

            if (ret.empty())
                return BasicVariable(BasicVariable::setNone);
            else if (ret.size() == 1)
                return ret.front();
            else return ret;
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
    else return pyNamespace::variableVector();
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
        const auto &stringVector = ctx->STRING();
        BasicVariable temps((std::string()));//todo 此处 "" 会构造 pyBoolean 类型对象
        for (auto i : stringVector)// 字符串首末有单/双引号且可以连续出现
            temps += BasicVariable(i->getText().substr(1, i->getText().length() - 2));
        return temps;
    } else if (ctx->NONE())
        return BasicVariable(BasicVariable::setNone);
    else if (ctx->TRUE())
        return BasicVariable(true);
    else if (ctx->FALSE())
        return BasicVariable(false);
    else if (ctx->test()) {
        const auto &testReturn = visitTest(ctx->test());
        if (testReturn.is<BasicVariable>())
            return testReturn;
    } else throw pyException("Unexpected Error in visitAtom()");
}

antlrcpp::Any EvalVisitor::visitTestlist(Python3Parser::TestlistContext *ctx)
//return pyNamespace::valueVector
{
#ifdef debug_info
    printf("visitTestlist\n");
    std::cout << ctx->getText() << std::endl;
#endif
    const auto &testVector = ctx->test();
    antlrcpp::Any testReturn;
    pyNamespace::valueVector retVector;
    for (auto i:testVector) {
        testReturn = visitTest(i);
        if (testReturn.is<BasicVariable>())
            retVector.emplace_back(testReturn.as<BasicVariable>());
            //todo 若test是个testlist，则等价于多个test
        else if (testReturn.is<pyNamespace::valueVector>()) {
            const pyNamespace::valueVector &testReturnVector
                    = testReturn.as<pyNamespace::valueVector>();
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
    pyNamespace::variableVector argVector;
    const auto &argumentCtxVector = ctx->argument();
    for (auto i:argumentCtxVector) {
        antlrcpp::Any argumentReturn = visitArgument(i);
        if (argumentReturn.is<BasicVariable>()) {
            const auto &argumentReturnValue = argumentReturn.as<BasicVariable>();
            argVector.emplace_back(std::make_pair(std::string(), Namespace.getValue(argumentReturnValue)));
        } else if (argumentReturn.is<pyNamespace::valueVector>()) {
            const auto &argumentReturnVector = argumentReturn.as<pyNamespace::valueVector>();
            for (auto i:argumentReturnVector)
                argVector.emplace_back(std::make_pair(std::string(), Namespace.getValue(i)));
        } else if (argumentReturn.is<std::pair<std::string, BasicVariable> >()) {
            const auto &argumentReturnPair = argumentReturn.as<std::pair<std::string, BasicVariable> >();
            argVector.emplace_back(std::make_pair(argumentReturnPair.first,
                                                  Namespace.getValue(argumentReturnPair.second)));
        } else throw pyException("Get Wrong Argument Return Type");
    }
    return argVector;
}

antlrcpp::Any EvalVisitor::visitArgument(Python3Parser::ArgumentContext *ctx) {
#ifdef debug_info
    printf("visitArgument\n");
    std::cout << ctx->getText() << std::endl;
#endif
    const auto &testVector = ctx->test();
    if (testVector.size() == 1)
        return visitTest(testVector.front());// 可能是 testlist
    else if (testVector.size() == 2)
        return std::make_pair(visitTest(testVector.front()).as<BasicVariable>().getName(),
                              visitTest(testVector.back()).as<BasicVariable>());
    else throw pyException("Argument with 0 or more than 2 Tests");
}
