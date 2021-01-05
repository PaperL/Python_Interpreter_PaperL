#include "Evalvisitor.h"

pyNamespace Namespace;

antlrcpp::Any EvalVisitor::visitFile_input(Python3Parser::File_inputContext *ctx) {
#ifdef basic_debug
    printf("visitFile_input\n");
    std::cout << ctx->getText() << std::endl;
#endif
    return visitChildren(ctx);
}

antlrcpp::Any EvalVisitor::visitFuncdef(Python3Parser::FuncdefContext *ctx) {
#ifdef basic_debug
    printf("visitFuncdef\n");
    std::cout << ctx->getText() << std::endl;
#endif
    return visitChildren(ctx);
}

antlrcpp::Any EvalVisitor::visitParameters(Python3Parser::ParametersContext *ctx) {
#ifdef basic_debug
    printf("visitParameters\n");
    std::cout << ctx->getText() << std::endl;
#endif
    return visitChildren(ctx);
}

antlrcpp::Any EvalVisitor::visitTypedargslist(Python3Parser::TypedargslistContext *ctx) {
#ifdef basic_debug
    printf("visitTypedargslist\n");
    std::cout << ctx->getText() << std::endl;
#endif
    return visitChildren(ctx);
}

antlrcpp::Any EvalVisitor::visitTfpdef(Python3Parser::TfpdefContext *ctx) {
#ifdef basic_debug
    printf("visitTfpdef\n");
    std::cout << ctx->getText() << std::endl;
#endif
    return visitChildren(ctx);
}

antlrcpp::Any EvalVisitor::visitStmt(Python3Parser::StmtContext *ctx) {
#ifdef basic_debug
    printf("visitStmt\n");
    std::cout << ctx->getText() << std::endl;
#endif
    return ((ctx -> simple_stmt() == nullptr) ? visitCompound_stmt(ctx -> compound_stmt()) : visitSimple_stmt(ctx -> simple_stmt()));
}

antlrcpp::Any EvalVisitor::visitSimple_stmt(Python3Parser::Simple_stmtContext *ctx) {
#ifdef basic_debug
    printf("visitSimple_stmt\n");
    std::cout << ctx->getText() << std::endl;
#endif
    return visitSmall_stmt(ctx -> small_stmt());
}

antlrcpp::Any EvalVisitor::visitSmall_stmt(Python3Parser::Small_stmtContext *ctx) {
#ifdef basic_debug
    printf("visitSmall_stmt\n");
    std::cout << ctx->getText() << std::endl;
#endif
    return ((ctx -> expr_stmt() == nullptr) ? visitFlow_stmt(ctx -> flow_stmt()) : visitExpr_stmt(ctx -> expr_stmt()));
}

antlrcpp::Any EvalVisitor::visitExpr_stmt(Python3Parser::Expr_stmtContext *ctx) {
#ifdef basic_debug
    printf("visitExpr_stmt\n");
    std::cout << ctx->getText() << std::endl;
#endif
    //todo @@@@@@@@
    visitTestlist(ctx->testlist().back()).as<
    return visitChildren(ctx);
}

antlrcpp::Any EvalVisitor::visitAugassign(Python3Parser::AugassignContext *ctx) {
#ifdef basic_debug
    printf("visitAugassign\n");
    std::cout << ctx->getText() << std::endl;
#endif
    return visitChildren(ctx);
}

antlrcpp::Any EvalVisitor::visitFlow_stmt(Python3Parser::Flow_stmtContext *ctx) {
#ifdef basic_debug
    printf("visitFlow_stmt\n");
    std::cout << ctx->getText() << std::endl;
#endif
    return visitChildren(ctx);
}

antlrcpp::Any EvalVisitor::visitBreak_stmt(Python3Parser::Break_stmtContext *ctx) {
#ifdef basic_debug
    printf("visitBreak_stmt\n");
    std::cout << ctx->getText() << std::endl;
#endif
    return visitChildren(ctx);
}

antlrcpp::Any EvalVisitor::visitContinue_stmt(Python3Parser::Continue_stmtContext *ctx) {
#ifdef basic_debug
    printf("visitContinue_stmt\n");
    std::cout << ctx->getText() << std::endl;
#endif
    return visitChildren(ctx);
}

antlrcpp::Any EvalVisitor::visitReturn_stmt(Python3Parser::Return_stmtContext *ctx) {
#ifdef basic_debug
    printf("visitReturn_stmt\n");
    std::cout << ctx->getText() << std::endl;
#endif
    return visitChildren(ctx);
}

antlrcpp::Any EvalVisitor::visitCompound_stmt(Python3Parser::Compound_stmtContext *ctx) {
#ifdef basic_debug
    printf("visitCompound_stmt\n");
    std::cout << ctx->getText() << std::endl;
#endif
    return visitChildren(ctx);
}

antlrcpp::Any EvalVisitor::visitIf_stmt(Python3Parser::If_stmtContext *ctx) {
#ifdef basic_debug
    printf("visitIf_stmt\n");
    std::cout << ctx->getText() << std::endl;
#endif
    return visitChildren(ctx);
}

antlrcpp::Any EvalVisitor::visitWhile_stmt(Python3Parser::While_stmtContext *ctx) {
#ifdef basic_debug
    printf("visitWhile_stmt\n");
    std::cout << ctx->getText() << std::endl;
#endif
    return visitChildren(ctx);
}

antlrcpp::Any EvalVisitor::visitSuite(Python3Parser::SuiteContext *ctx) {
#ifdef basic_debug
    printf("visitSuite\n");
    std::cout << ctx->getText() << std::endl;
#endif
    return visitChildren(ctx);
}

antlrcpp::Any EvalVisitor::visitTest(Python3Parser::TestContext *ctx) {
#ifdef basic_debug
    printf("visitTest\n");
    std::cout << ctx->getText() << std::endl;
#endif
    return visitChildren(ctx);
}

antlrcpp::Any EvalVisitor::visitOr_test(Python3Parser::Or_testContext *ctx) {
#ifdef basic_debug
    printf("visitOr_test\n");
    std::cout << ctx->getText() << std::endl;
#endif
    return visitChildren(ctx);
}

antlrcpp::Any EvalVisitor::visitAnd_test(Python3Parser::And_testContext *ctx) {
#ifdef basic_debug
    printf("visitAnd_test\n");
    std::cout << ctx->getText() << std::endl;
#endif
    return visitChildren(ctx);
}

antlrcpp::Any EvalVisitor::visitNot_test(Python3Parser::Not_testContext *ctx) {
#ifdef basic_debug
    printf("visitNot_test\n");
    std::cout << ctx->getText() << std::endl;
#endif
    return visitChildren(ctx);
}

antlrcpp::Any EvalVisitor::visitComparison(Python3Parser::ComparisonContext *ctx) {
#ifdef basic_debug
    printf("visitComparison\n");
    std::cout << ctx->getText() << std::endl;
#endif
    return visitChildren(ctx);
}

antlrcpp::Any EvalVisitor::visitComp_op(Python3Parser::Comp_opContext *ctx) {
#ifdef basic_debug
    printf("visitComp_op\n");
    std::cout << ctx->getText() << std::endl;
#endif
    return visitChildren(ctx);
}

antlrcpp::Any EvalVisitor::visitArith_expr(Python3Parser::Arith_exprContext *ctx) {
#ifdef basic_debug
    printf("visitArith_expr\n");
    std::cout << ctx->getText() << std::endl;
#endif
    return visitChildren(ctx);
}

antlrcpp::Any EvalVisitor::visitAddorsub_op(Python3Parser::Addorsub_opContext *ctx) {
#ifdef basic_debug
    printf("visitAddorsub_op\n");
    std::cout << ctx->getText() << std::endl;
#endif
    return visitChildren(ctx);
}

antlrcpp::Any EvalVisitor::visitTerm(Python3Parser::TermContext *ctx) {
#ifdef basic_debug
    printf("visitTerm\n");
    std::cout << ctx->getText() << std::endl;
#endif
    return visitChildren(ctx);
}

antlrcpp::Any EvalVisitor::visitMuldivmod_op(Python3Parser::Muldivmod_opContext *ctx) {
#ifdef basic_debug
    printf("visitMuldivmod_op\n");
    std::cout << ctx->getText() << std::endl;
#endif
    return visitChildren(ctx);
}

antlrcpp::Any EvalVisitor::visitFactor(Python3Parser::FactorContext *ctx) {
#ifdef basic_debug
    printf("visitFactor\n");
    std::cout << ctx->getText() << std::endl;
#endif
    return visitChildren(ctx);
}

antlrcpp::Any EvalVisitor::visitAtom_expr(Python3Parser::Atom_exprContext *ctx) {
#ifdef basic_debug
    printf("visitAtom_expr\n");
    std::cout << ctx->getText() << std::endl;
#endif
    return visitChildren(ctx);
}

antlrcpp::Any EvalVisitor::visitTrailer(Python3Parser::TrailerContext *ctx) {
#ifdef basic_debug
    printf("visitTrailer\n");
    std::cout << ctx->getText() << std::endl;
#endif
    return visitChildren(ctx);
}

antlrcpp::Any EvalVisitor::visitAtom(Python3Parser::AtomContext *ctx) {
#ifdef basic_debug
    printf("visitAtom\n");
    std::cout << ctx->getText() << std::endl;
#endif
    if (ctx->NAME()) {

        //todo @@@返回变量对应的内容
    } else if (ctx->NUMBER()) {
        if (ctx->getText().find('.') == std::string::npos)
            return BasicVariable(HighPrecision(ctx->getText()));
        else
            return BasicVariable(stod(ctx->getText()));//todo 此处可能抛出异常
    } else if (!ctx->STRING().empty()) {
        BasicVariable temps("");
        for (auto i : ctx->STRING())
            temps += BasicVariable(i->getText().substr(1, i->getText().length() - 2));//字符串首末有双引号
        return temps;
    } else if (ctx->test()) {
        return visitTest(ctx->test());
    } else return BasicVariable();
}

antlrcpp::Any EvalVisitor::visitTestlist(Python3Parser::TestlistContext *ctx) {
#ifdef basic_debug
    printf("visitTestlist\n");
    std::cout << ctx->getText() << std::endl;
#endif
    return visitChildren(ctx);
}

antlrcpp::Any EvalVisitor::visitArglist(Python3Parser::ArglistContext *ctx) {
#ifdef basic_debug
    printf("visitArglist\n");
    std::cout << ctx->getText() << std::endl;
#endif
    return visitChildren(ctx);
}

antlrcpp::Any EvalVisitor::visitArgument(Python3Parser::ArgumentContext *ctx) {
#ifdef basic_debug
    printf("visitArgument\n");
    std::cout << ctx->getText() << std::endl;
#endif
    return visitChildren(ctx);
}
