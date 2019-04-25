//
// Created by blackgeorge on 4/6/19.
//

#ifndef LLVM_EXAMPLE_LEXER_H
#define LLVM_EXAMPLE_LEXER_H

#include <iostream>

// The lexer returns tokens [0-255] if it is an unknown character,
// otherwise one of these for known things.
enum Token {
    tok_eof = -1,

    // commands
    tok_def = -2,
    tok_extern = -3,

    // primary
    tok_identifier = -4,
    tok_number = -5,

    // control
    tok_if = -6,
    tok_then = -7,
    tok_else = -8
};

extern std::string IdentifierStr; // Filled in if tok_identifier
extern double NumVal;             // Filled in if tok_number

/// gettok - Return the next token from standard input.
int gettok();

#endif //LLVM_EXAMPLE_LEXER_H
