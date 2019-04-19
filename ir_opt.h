//
// Created by blackgeorge on 4/19/19.
//

#ifndef LLVM_EXAMPLE_IR_OPT_H
#define LLVM_EXAMPLE_IR_OPT_H

#include <bits/unique_ptr.h>
#include "ast.h"

extern std::unique_ptr<llvm::legacy::FunctionPassManager> TheFPM;

void InitializeModuleAndPassManager();

#endif //LLVM_EXAMPLE_IR_OPT_H
