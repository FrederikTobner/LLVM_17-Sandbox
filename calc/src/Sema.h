#ifndef SEMA_H
#define SEMA_H

#include "AST.h"
#include "Lexer.h"

/// @brief Semantic analysis class
/// @details This class performs semantic analysis on the AST
class Sema {
public:
  /// @brief Perform semantic analysis
  /// @param Tree - The AST to analyze
  /// @return bool - True if the analysis was successful
  bool semantic(AST *Tree);
};

#endif
