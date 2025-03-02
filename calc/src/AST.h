#ifndef AST_H
#define AST_H
// Includes LLVM's SmallVector class. This class is a vector optimized for small sizes.
#include "llvm/ADT/SmallVector.h"
// Includes LLVM's StringRef class. This class is does not require a null terminator.
#include "llvm/ADT/StringRef.h"

// Forward declarations of classes
class AST;
class Expr;
class Factor;
class BinaryOp;
class WithDecl;

/// @brief Visitor class for the AST 
/// @details This class is the base class for all visitors of the AST. It provides
/// a visit method for each AST node.
class ASTVisitor {
public:
  virtual void visit(AST &){};
  virtual void visit(Expr &){};
  virtual void visit(Factor &) = 0;
  virtual void visit(BinaryOp &) = 0;
  virtual void visit(WithDecl &) = 0;
};

/// @brief Abstract syntax tree class 
/// @details This class is the base class for all AST nodes. It provides a virtual
/// destructor and a virtual accept method for the visitor pattern.
class AST {
public:
  virtual ~AST() {}
  virtual void accept(ASTVisitor &V) = 0;
};

/// @brief Expression class 
/// @details This class is the base class for all expressions in the AST.
class Expr : public AST {
public:
  Expr() {}
};

/// @brief Factor class 
/// @details This class represents a factor in the AST.
class Factor : public Expr {
public:
  enum ValueKind { Ident, Number };

private:
  ValueKind Kind;
  llvm::StringRef Val;

public:
  Factor(ValueKind Kind, llvm::StringRef Val)
      : Kind(Kind), Val(Val) {}
  ValueKind getKind() { return Kind; }
  llvm::StringRef getVal() { return Val; }
  virtual void accept(ASTVisitor &V) override {
    V.visit(*this);
  }
};

/// @brief Binary operation class 
/// @details This class represents a binary operation in the AST.
class BinaryOp : public Expr {
public:
  enum Operator { Plus, Minus, Mul, Div };

private:
  Expr *Left;
  Expr *Right;
  Operator Op;

public:
  BinaryOp(Operator Op, Expr *L, Expr *R)
      : Op(Op), Left(L), Right(R) {}
  Expr *getLeft() { return Left; }
  Expr *getRight() { return Right; }
  Operator getOperator() { return Op; }
  virtual void accept(ASTVisitor &V) override {
    V.visit(*this);
  }
};

/// @brief With declaration class 
/// @details This class represents a with declaration in the AST.
class WithDecl : public AST {
  using VarVector = llvm::SmallVector<llvm::StringRef, 8>;
  VarVector Vars;
  Expr *E;

public:
  WithDecl(llvm::SmallVector<llvm::StringRef, 8> Vars,
           Expr *E)
      : Vars(Vars), E(E) {}
  VarVector::const_iterator begin() { return Vars.begin(); }
  VarVector::const_iterator end() { return Vars.end(); }
  Expr *getExpr() { return E; }
  virtual void accept(ASTVisitor &V) override {
    V.visit(*this);
  }
};
#endif
