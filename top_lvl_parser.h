//
// Created by blackgeorge on 4/7/19.
//

#ifndef LLVM_EXAMPLE_TOP_LVL_PARSER_H
#define LLVM_EXAMPLE_TOP_LVL_PARSER_H

#include "parser.h"

void HandleDefinition();

void HandleExtern();

void HandleTopLevelExpression();

/// top ::= definition | external | expression | ';'
void MainLoop();

#endif //LLVM_EXAMPLE_TOP_LVL_PARSER_H
