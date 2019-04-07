//
// Created by blackgeorge on 4/7/19.
//

#ifndef LLVM_EXAMPLE_PARSER_H
#define LLVM_EXAMPLE_PARSER_H

#include "lexer.h"

/// CurTok/getNextToken - Provide a simple token buffer.
///
/// CurTok is the current token the parser is looking at.
static int CurTok;

/// getNextToken reads another token from the
/// lexer and updates CurTok with its results.
int getNextToken();

#endif //LLVM_EXAMPLE_PARSER_H
