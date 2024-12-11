#ifndef LEXER_H
#define LEXER_H

#include "llvm/ADT/StringRef.h"
#include "llvm/Support/MemoryBuffer.h"

class Lexer;

class Token {
  friend class Lexer;

public:
  enum TokenKind : unsigned short {
    eoi,        // End of input
    unknown,    // unknown token type
    ident,      // foo
    number,     // 123
    comma,      // ,
    colon,      // :
    plus,       // +
    minus,      // -
    star,       // *
    slash,      // /
    l_paren,    // (
    r_paren,    // )
    KW_with     // with
  };

private:
  TokenKind Kind;
  llvm::StringRef Text;

public:
  TokenKind getKind() const { return Kind; }
  llvm::StringRef getText() const {
    return Text;
  }

  bool is(TokenKind K) const { return Kind == K; }
  bool isOneOf(TokenKind K1, TokenKind K2) const {
    return is(K1) || is(K2);
  }
  
  template <typename... Ts>
  bool isOneOf(TokenKind K1, TokenKind K2, Ts... Ks) const {
    // expands template down until only 2 token kinds are left
    return is(K1) || isOneOf(K2, Ks...);
  }
};

class Lexer {
  const char *BufferStart;
  const char *BufferPtr;

public:
  Lexer(const llvm::StringRef &Buffer) {
    BufferStart = Buffer.begin();
    BufferPtr = BufferStart;
  }

  /// @brief Returns the next token from the input.
  /// @param token The next token.
  void next(Token &token);

private:
  /// @brief Form a token with the given kind and text.
  /// @param Result The token to form.
  /// @param TokEnd The end of the token.
  /// @param Kind The kind of the token.
  void formToken(Token &Result, const char *TokEnd,
                 Token::TokenKind Kind);
};
#endif