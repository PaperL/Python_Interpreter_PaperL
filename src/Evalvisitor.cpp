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
    return visitChildren(ctx);
}

antlrcpp::Any EvalVisitor::visitOr_test(Python3Parser::Or_testContext *ctx) {
#ifdef debug_info
    printf("visitOr_test\n");
    std::cout << ctx->getText() << std::endl;
#endif
    return visitChildren(ctx);
}

antlrcpp::Any EvalVisitor::visitAnd_test(Python3Parser::And_testContext *ctx) {
#ifdef debug_info
    printf("visitAnd_test\n");
    std::cout << ctx->getText() << std::endl;
#endif
    return visitChildren(ctx);
}

antlrcpp::Any EvalVisitor::visitNot_test(Python3Parser::Not_testContext *ctx) {
#ifdef debug_info
    printf("visitNot_test\n");
    std::cout << ctx->getText() << std::endl;
#endif
    return visitChildren(ctx);
}

antlrcpp::Any EvalVisitor::visitComparison(Python3Parser::ComparisonContext *ctx) {
#ifdef debug_info
    printf("visitComparison\n");
    std::cout << ctx->getText() << std::endl;
#endif
    return visitChildren(ctx);
}

antlrcpp::Any EvalVisitor::visitComp_op(Python3Parser::Comp_opContext *ctx) {
#ifdef debug_info
    printf("visitComp_op\n");
    std::cout << ctx->getText() << std::endl;
#endif
    return visitChildren(ctx);
}

antlrcpp::Any EvalVisitor::visitArith_expr(Python3Parser::Arith_exprContext *ctx) {
#ifdef debug_info
    printf("visitArith_expr\n");
    std::cout << ctx->getText() << std::endl;
#endif
    return visitChildren(ctx);
}

antlrcpp::Any EvalVisitor::visitAddorsub_op(Python3Parser::Addorsub_opContext *ctx) {
#ifdef debug_info
    printf("visitAddorsub_op\n");
    std::cout << ctx->getText() << std::endl;
#endif
    return visitChildren(ctx);
}

antlrcpp::Any EvalVisitor::visitTerm(Python3Parser::TermContext *ctx) {
#ifdef debug_info
    printf("visitTerm\n");
    std::cout << ctx->getText() << std::endl;
#endif
    return visitChildren(ctx);
}

antlrcpp::Any EvalVisitor::visitMuldivmod_op(Python3Parser::Muldivmod_opContext *ctx) {
#ifdef debug_info
    printf("visitMuldivmod_op\n");
    std::cout << ctx->getText() << std::endl;
#endif
    return visitChildren(ctx);
}

antlrcpp::Any EvalVisitor::visitFactor(Python3Parser::FactorContext *ctx) {
#ifdef debug_info
    printf("visitFactor\n");
    std::cout << ctx->getText() << std::endl;
#endif
    return visitChildren(ctx);
}

antlrcpp::Any EvalVisitor::visitAtom_expr(Python3Parser::Atom_exprContext *ctx) {
#ifdef debug_info
    printf("visitAtom_expr\n");
    std::cout << ctx->getText() << std::endl;
#endif
    if (!ctx->trailer()) return visitAtom(ctx->atom());//非函数则直接返回Atom（BasicVariable）
    else {
        BasicVariable atom = visitAtom(ctx->atom());
        if (atom.getType() != BasicVariable::pyName)
            throw pyException("Atom for Function Name is not pyName Type");

        if (atom.getName() == "print") {//python不允许print(a=b)，即赋值语句无返回值

        } else if (atom.getName() == "bool") {

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

antlrcpp::Any EvalVisitor::visitTrailer(Python3Parser::TrailerContext *ctx) {
#ifdef debug_info
    printf("visitTrailer\n");
    std::cout << ctx->getText() << std::endl;
#endif
    return visitChildren(ctx);
}

antlrcpp::Any EvalVisitor::visitAtom(Python3Parser::AtomContext *ctx) {
#ifdef debug_info
    printf("visitAtom\n");
    std::cout << ctx->getText() << std::endl;
#endif
    if (ctx->NAME())
        return BasicVariable(ctx->NAME()->getText(), BasicVariable::setName);//todo 此处需确认返回内容
    else if (ctx->NUMBER()) {
        if (ctx->getText().find('.') == std::string::npos)
            return BasicVariable(HighPrecision(ctx->getText()));
        else return BasicVariable(stod(ctx->getText()));//todo 此处可能抛出异常
    } else if (!ctx->STRING().empty()) {
        BasicVariable temps("");
        for (auto i : ctx->STRING())
            temps += BasicVariable(i->getText().substr(1, i->getText().length() - 2));//字符串首末有双引号
        return temps;
    } else if (ctx->NONE())
        return BasicVariable(BasicVariable::setNone);
    else return BasicVariable();
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
    return visitChildren(ctx);
}

antlrcpp::Any EvalVisitor::visitArgument(Python3Parser::ArgumentContext *ctx) {
#ifdef debug_info
    printf("visitArgument\n");
    std::cout << ctx->getText() << std::endl;
#endif
    return visitChildren(ctx);
}
