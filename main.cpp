#include <iostream>
#include <fstream>
#include <bits/unique_ptr.h>
#include <vector>
#include <map>

#include "lexer.h"
#include "ast.h"
#include "parser.h"
#include "top_lvl_parser.h"
#include "ir_opt.h"

//using namespace llvm;

//namespace {
//} // end anonymous namespace

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

    InitializeModuleAndPassManager();

    // Run the main "interpreter loop" now.
    MainLoop();

    // Print out all of the generated code.
    TheModule->print(llvm::errs(), nullptr);

    return 0;
}