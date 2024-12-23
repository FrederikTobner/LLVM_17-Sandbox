#include "CodeGen.h"
#include "Parser.h"
#include "Sema.h"
#include "llvm/Support/CommandLine.h"
#include "llvm/Support/InitLLVM.h"
#include "llvm/Support/raw_ostream.h"

// Command line options
static llvm::cl::opt<std::string>
    Input(llvm::cl::Positional,
          llvm::cl::desc("<input expression>"),
          llvm::cl::init(""));

/// @brief Main entry point of the calc compiler
/// @param argc Number of command line arguments
/// @param argv Command line arguments
/// @return 0 on success, 1 on failure
int main(int argc, const char **argv) {
  llvm::InitLLVM X(argc, argv);
  llvm::cl::ParseCommandLineOptions(
      argc, argv, "calc - the expression compiler\n");

  Lexer Lex(Input);
  Parser Parser(Lex);
  AST *Tree = Parser.parse();
  if (!Tree || Parser.hasError()) {
    llvm::errs() << "Syntax errors occured\n";
    return 1;
  }
  Sema Semantic;
  if (Semantic.semantic(Tree)) {
    llvm::errs() << "Semantic errors occured\n";
    return 1;
  }
  CodeGen CodeGenerator;
  CodeGenerator.compile(Tree);
  return 0;
}
