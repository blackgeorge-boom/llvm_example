//
// Created by blackgeorge on 4/19/19.
//

#include "ir_opt.h"

std::unique_ptr<llvm::legacy::FunctionPassManager> TheFPM;

void InitializeModuleAndPassManager()
{
    // Open a new module.
    TheModule = llvm::make_unique<llvm::Module>("my cool jit", TheContext);

    // Create a new pass manager attached to it.
    TheFPM = llvm::make_unique<llvm::legacy::FunctionPassManager>(TheModule.get());

    // Do simple "peephole" optimizations and bit-twiddling optimizations.
    TheFPM->add(llvm::createInstructionCombiningPass());

    // Reassociate expressions.
    TheFPM->add(llvm::createReassociatePass());

    // Eliminate Common SubExpressions.
    TheFPM->add(llvm::createGVNPass());

    // Simplify the control flow graph (deleting unreachable blocks, etc).
    TheFPM->add(llvm::createCFGSimplificationPass());

    TheFPM->doInitialization();
}
