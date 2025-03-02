#ifndef CODEGEN_H
#define CODEGEN_H

#include "AST.h"

/// @brief Code generation clas
class CodeGen
{
public:
 /// @brief Compile the AST to LLVM IR
 /// @param Tree The AST to compile
 void compile(AST *Tree);

};
#endif
