//
// Created by blackgeorge on 4/7/19.
//

#include "top_lvl_parser.h"

void HandleDefinition() {
    if (auto FnAST = ParseDefinition()) {
        if (auto* FnIR = FnAST->codegen()) {
            fprintf(stderr, "Parsed a function definition:");
            FnIR->print(llvm::errs());
            fprintf(stderr, "\n");
        }
    }
    else {
        // Skip token for error recovery.
        getNextToken();
    }
}

void HandleExtern() {
    if (auto ProtoAST = ParseExtern()) {
        if (auto* ProtoIR = ProtoAST->codegen()){
            fprintf(stderr, "Parsed a function extern:");
            ProtoIR->print(llvm::errs());
            fprintf(stderr, "\n");
        }
    }
    else {
        // Skip token for error recovery.
        getNextToken();
    }
}

void HandleTopLevelExpression() {
    // Evaluate a top-level expression into an anonymous function.
    if (auto FnAST = ParseTopLevelExpr()) {
        if (auto *FnIR = FnAST->codegen()) {
            fprintf(stderr, "Parsed a top-level expr:");
            FnIR->print(llvm::errs());
            fprintf(stderr, "\n");
        }
    } else {
        // Skip token for error recovery.
        getNextToken();
    }
}

void MainLoop() {
    while (true) {
        fprintf(stderr, "ready> ");
        switch (CurTok) {
            case tok_eof:
                fprintf(stderr, "eof ");
                return;
            case ';':
                fprintf(stderr, "; ");
                // if you parse it you get nullptr as AST
                getNextToken();
                break;
            case tok_def:
                fprintf(stderr, "def ");
                HandleDefinition();
                break;
            case tok_extern:
                fprintf(stderr, "extern ");
                HandleExtern();
                break;
            default:
                fprintf(stderr, "top ");
                HandleTopLevelExpression();
                break;
        }
    }
}
