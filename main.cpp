#include <iostream>
#include <fstream>
#include <bits/unique_ptr.h>
#include <vector>
#include <map>
#include "llvm/ADT/APFloat.h"
#include "llvm/ADT/STLExtras.h"
#include "llvm/IR/BasicBlock.h"
#include "llvm/IR/Constants.h"
#include "llvm/IR/DerivedTypes.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Type.h"
#include "llvm/IR/Verifier.h"

#include "lexer.h"
#include "ast.h"
#include "parser.h"
//#include "top_lvl_parser.h"

//using namespace llvm;

//===----------------------------------------------------------------------===//
// Abstract Syntax Tree (aka Parse Tree)
//===----------------------------------------------------------------------===//

//namespace {
//} // end anonymous namespace



//===----------------------------------------------------------------------===//
// Code Generation
//===----------------------------------------------------------------------===//

//static llvm::LLVMContext TheContext;
//static llvm::IRBuilder<> Builder(TheContext);
//static std::unique_ptr<llvm::Module> TheModule;
//static std::map<std::string, llvm::Value *> NamedValues;


//===----------------------------------------------------------------------===//
// Main driver code.
//===----------------------------------------------------------------------===//

static void HandleDefinition() {
    if (auto FnAST = ParseDefinition()) {
        if (auto *FnIR = FnAST->codegen()) {
            fprintf(stderr, "Read function definition:");
            FnIR->print(llvm::errs());
            fprintf(stderr, "\n");
        }
    } else {
        getNextToken();
    }
}

static void HandleExtern() {
    if (auto ProtoAST = ParseExtern()) {
        if (auto *FnIR = ProtoAST->codegen()) {
            fprintf(stderr, "Read extern:");
            FnIR->print(llvm::errs());
            fprintf(stderr, "\n");
        }
    } else {
        getNextToken();
    }
}

static void HandleTopLevelExpression() {
    if (auto FnAST = ParseTopLevelExpr()) {
        if (auto *FnIR = FnAST->codegen()) {
            fprintf(stderr, "Read top-level expression:");
            FnIR->print(llvm::errs());
            fprintf(stderr, "\n");
        }
    } else {
        getNextToken();
    }
}

static void MainLoop() {
    while (true) {
        fprintf(stderr, "ready> ");

        switch (CurTok) {
            case tok_eof:
                return;
            case ';':
                getNextToken();
                break;
            case tok_def:
                HandleDefinition();
                break;
            case tok_extern:
                HandleExtern();
                break;
            default:
                HandleTopLevelExpression();
                break;
        }
    }
}

int main()
{
    // Install standard binary operators.
    // 1 is lowest precedence.
    BinopPrecedence['<'] = 10;
    BinopPrecedence['+'] = 20;
    BinopPrecedence['-'] = 20;
    BinopPrecedence['*'] = 40; // highest.

    // Prime the first token.
    fprintf(stderr, "ready> ");
    getNextToken();

    // Make the module, which holds all the code.
    TheModule = llvm::make_unique<llvm::Module>("my cool jit", TheContext);

    // Run the main "interpreter loop" now.
    MainLoop();

    // Print out all of the generated code.
    TheModule->print(llvm::errs(), nullptr);

    return 0;
}