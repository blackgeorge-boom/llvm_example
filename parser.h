//
// Created by blackgeorge on 4/7/19.
//

#ifndef LLVM_EXAMPLE_PARSER_H
#define LLVM_EXAMPLE_PARSER_H

#include <map>
#include "lexer.h"
#include "ast.h"

/// CurTok/getNextToken - Provide a simple token buffer.
///
/// CurTok is the current token the parser is looking at.
static int CurTok;

/// getNextToken reads another token from the
/// lexer and updates CurTok with its results.
int getNextToken();

/// BinopPrecedence - This holds the precedence for each binary operator that is
/// defined.
static std::map<char, int> BinopPrecedence;

/// GetTokPrecedence - Get the precedence of the pending binary operator token.
int GetTokPrecedence();

/// LogError* - These are little helper functions for error handling.
std::unique_ptr<ExprAST> LogError(const char *Str);
std::unique_ptr<PrototypeAST> LogErrorP(const char *Str);

/// numberexpr ::= number
std::unique_ptr<ExprAST> ParseNumberExpr();

/// parenexpr ::= '(' expression ')'
std::unique_ptr<ExprAST> ParseParenExpr();

/// identifierexpr
///   ::= identifier
///   ::= identifier '(' expression* ')'
std::unique_ptr<ExprAST> ParseIdentifierExpr();

/// primary
///   ::= identifierexpr
///   ::= numberexpr
///   ::= parenexpr
std::unique_ptr<ExprAST> ParsePrimary();

/// binoprhs
///   ::= ('+' primary)*
std::unique_ptr<ExprAST> ParseBinOpRHS(int ExprPrec,
                                              std::unique_ptr<ExprAST> LHS);

/// expression
///   ::= primary binoprhs
///
std::unique_ptr<ExprAST> ParseExpression();

/// prototype
///   ::= id '(' id* ')'
std::unique_ptr<PrototypeAST> ParsePrototype();

/// definition ::= 'def' prototype expression
std::unique_ptr<FunctionAST> ParseDefinition();

/// toplevelexpr ::= expression
std::unique_ptr<FunctionAST> ParseTopLevelExpr();

/// external ::= 'extern' prototype
std::unique_ptr<PrototypeAST> ParseExtern();

#endif //LLVM_EXAMPLE_PARSER_H
