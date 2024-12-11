#ifndef PARSER_H
#define PARSER_H

#include "AST.h"
#include "Lexer.h"
#include "llvm/Support/raw_ostream.h"

class Parser {
  Lexer &Lex;
  Token Tok;
  bool HasError;

  /// @brief Report an error
  void error() {
    llvm::errs() << "Unexpected: " << Tok.getText() << "\n";
    HasError = true;
  }

  /// @brief Advance the lexer
  void advance() { Lex.next(Tok); }

  /// @brief Check if the current token is of a certain kind
  /// @param Kind - The kind of token to check
  /// @return bool - True if the token is of the specified kind
  bool expect(Token::TokenKind Kind) {
    if (!Tok.is(Kind)) {
      error();
      return true;
    }
    return false;
  }

  /// @brief Consume a token
  /// @param Kind - The kind of token to consume
  /// @return bool - True if the token was consumed
  bool consume(Token::TokenKind Kind) {
    if (expect(Kind))
      return true;
    advance();
    return false;
  }

  /// @brief Parse a calc
  /// @return AST* - The parsed AST
  AST *parseCalc();

  /// @brief Parse a with decl
  /// @return WithDecl* - The parsed with decl
  Expr *parseExpr();

  /// @brief Parse a term
  /// @return Expr* - The parsed term
  Expr *parseTerm();

  /// @brief Parse a factor
  /// @return Expr* - The parsed factor
  Expr *parseFactor();

public:
  Parser(Lexer &Lex) : Lex(Lex), HasError(false) {
    advance();
  }
  
  /// @brief Parse the input
  /// @return AST* - The parsed AST
  AST *parse();

  /// @brief Check if there was an error
  /// @return bool - True if there was an error
  bool hasError() { return HasError; }
};

#endif