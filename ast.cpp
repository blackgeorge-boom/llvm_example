//
// Created by blackgeorge on 4/11/19.
//


#include "ast.h"

llvm::Value* LogErrorV(const char *Str)
{
    fprintf(stderr, "Error %s\n", Str);
    return nullptr;
}

llvm::Value* NumberExprAST::codegen()
{
    return llvm::ConstantFP::get(TheContext, llvm::APFloat(Val));
}


llvm::Value *VariableExprAST::codegen()
{
    return nullptr;
}

llvm::Value *BinaryExprAST::codegen()
{
    return nullptr;
}

llvm::Value *CallExprAST::codegen()
{
    return nullptr;
}

llvm::Function *PrototypeAST::codegen()
{
    return nullptr;
}

llvm::Function *FunctionAST::codegen()
{
    return nullptr;
}
