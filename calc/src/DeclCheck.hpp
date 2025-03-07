#pragma once

#include "llvm/ADT/StringSet.h"
#include "llvm/Support/raw_ostream.h"

namespace {

/// @brief A visitor for checking variable declarations
class DeclCheck : public ASTVisitor {
  llvm::StringSet<> Scope;
  bool HasError;

  /// @brief Error types for variable declarations
  enum ErrorType { Twice, Not };

  /// @brief Report an error
  /// @param ET - The type of error
  /// @param V - The variable name
  void error(ErrorType ET, llvm::StringRef V) {
    llvm::errs() << "Variable " << V << " "
                 << (ET == Twice ? "already" : "not")
                 << " declared\n";
    HasError = true;
  }

public:
  DeclCheck() : HasError(false) {}

  bool hasError() { return HasError; }

  /// @brief Visit a Factor node
  /// @param Node - The Factor node
  virtual void visit(Factor &Node) override {
    if (Node.getKind() == Factor::Ident) {
      if (Scope.find(Node.getVal()) == Scope.end())
        error(Not, Node.getVal());
    }
  };

  /// @brief Visit a BinaryOp node
  /// @param Node - The BinaryOp node
  virtual void visit(BinaryOp &Node) override {
    if (Node.getLeft())
      Node.getLeft()->accept(*this);
    else
      HasError = true;
    if (Node.getRight())
      Node.getRight()->accept(*this);
    else
      HasError = true;
  };

  /// @brief Visit a WithDecl node
  /// @param Node - The WithDecl node
  virtual void visit(WithDecl &Node) override {
    for (auto I = Node.begin(), E = Node.end(); I != E;
         ++I) {
      if (!Scope.insert(*I).second)
        error(Twice, *I);
    }
    if (Node.getExpr())
      Node.getExpr()->accept(*this);
    else
      HasError = true;
  };
};
}