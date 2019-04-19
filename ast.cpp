//
// Created by blackgeorge on 4/11/19.
//

#include "ast.h"
#include "logger.h"

llvm::LLVMContext TheContext;
llvm::IRBuilder<> Builder(TheContext);
std::unique_ptr<llvm::Module> TheModule;
std::map<std::string, llvm::Value *> NamedValues;

llvm::Value* NumberExprAST::codegen()
{
    return llvm::ConstantFP::get(TheContext, llvm::APFloat(Val));
}


llvm::Value* VariableExprAST::codegen()
{
    // Look this variable up in the function.
    llvm::Value* V = NamedValues[Name];
    if (!V)
        return LogErrorV("Unknown variable name");
    return V;
}

llvm::Value* BinaryExprAST::codegen()
{
    llvm::Value* L = LHS->codegen();
    llvm::Value* R = RHS->codegen();

    if (!L || !R)
        return nullptr;

    switch (Op) {
        case '+':
            return Builder.CreateFAdd(L, R, "addtmp");
        case '-':
            return Builder.CreateFSub(L, R, "subtmp");
        case '*':
            return Builder.CreateFMul(L, R, "multmp");
        case '<':
            L = Builder.CreateFCmpULT(L, R, "cmptmp");
            // Convert bool 0/1 to double 0.0 or 1.0
            return Builder.CreateUIToFP(L, llvm::Type::getDoubleTy(TheContext),
                                        "booltmp");
        default:
            return LogErrorV("Invalid binary operator");
    }
}

llvm::Value* CallExprAST::codegen()
{
    // Look up the name in the global module table.
    llvm::Function* CalleeF = TheModule->getFunction(Callee);
    if (!CalleeF)
        return LogErrorV("Unknown function referenced");

    // If argument mismatch error.
    if (CalleeF->arg_size() != Args.size())
        return LogErrorV("Incorrect # arguments passed");

    std::vector<llvm::Value*> ArgsV;
    for (unsigned long i = 0, e = Args.size(); i != e; ++i) {
        ArgsV.push_back(Args[i]->codegen());
        if (!ArgsV.back())
            return nullptr;
    }

    return Builder.CreateCall(CalleeF, ArgsV, "calltmp");
}

llvm::Function* PrototypeAST::codegen()
{
    // Make the function type: double(double,double) etc.
    std::vector<llvm::Type*> Doubles(Args.size(),
                                     llvm::Type::getDoubleTy(TheContext));

    llvm::FunctionType* FT =
            llvm::FunctionType::get(llvm::Type::getDoubleTy(TheContext),
                                    Doubles, false);

    llvm::Function* F =
            llvm::Function::Create(FT, llvm::Function::ExternalLinkage,
                                   Name, TheModule.get());

    // Set names for all arguments.
    unsigned Idx = 0;
    for (auto& Arg : F->args())
        Arg.setName(Args[Idx++]);

    return F;
}

llvm::Function *FunctionAST::codegen()
{
    llvm::Function* TheFunction = TheModule->getFunction(Proto->getName());

    if (!TheFunction)
        TheFunction = Proto->codegen();

    if (!TheFunction)
        return nullptr;

//    if (!TheFunction->empty())
//        return (llvm::Function*)LogErrorV("Function cannot be redefined.") ;

    // Create a new basic block to start insertion into.
    llvm::BasicBlock* BB = llvm::BasicBlock::Create(TheContext, "entry", TheFunction);
    Builder.SetInsertPoint(BB);

    // Record the function arguments in the NamedValues map.
    NamedValues.clear();
    for (auto& Arg : TheFunction->args())
        NamedValues[Arg.getName()] = &Arg;

    if (llvm::Value* RetVal = Body->codegen()) {
        // Finish off the function.
        Builder.CreateRet(RetVal);

        // Validate the generated code, checking for consistency.
        llvm::verifyFunction(*TheFunction);

        return TheFunction;
    }

    // Error reading body, remove function.
    TheFunction->eraseFromParent();

    return nullptr;
}
