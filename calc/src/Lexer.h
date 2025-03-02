#ifndef LEXER_H
#define LEXER_H

// Contains a C string and its length. Therefor no null terminator is required.
#include "llvm/ADT/StringRef.h"
// Provides read-only access to a a block of memory, filled with the contents of a file.
// On requestm a null-terminator can added to the end of the file.
#include "llvm/Support/MemoryBuffer.h"

// Forward declaration of the Lexer class
class Lexer;

/// @brief Token class
class Token {
  friend class Lexer;

public:
  /// @brief Token types of the lexer
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
  /// @brief Get the kind of the token.
  /// @return The kind of the token.
  TokenKind getKind() const { return Kind; }

  /// @brief Get the text of the token.
  /// @return The text of the token.
  llvm::StringRef getText() const {
    return Text;
  }
  /// @brief Check if the token is of the given kind.
  /// @param K The token kind.
  /// @return True if the token is of the given kind.
  bool is(TokenKind K) const { return Kind == K; }

  /// @brief Check if the token is one of the given kinds.
  /// @param K1 The first token kind.
  /// @param K2 The second token kind.
  /// @return True if the token is one of the given kinds.
  bool isOneOf(TokenKind K1, TokenKind K2) const {
    return is(K1) || is(K2);
  }
  
  /// @brief Check if the token is one of the given kinds.
  /// @tparam Ts The token kinds.
  /// @param K1 The first token kind.
  /// @param K2 The second token kind.
  /// @param Ks The remaining token kinds.
  /// @return True if the token is one of the given kinds.
  template <typename... Ts>
  bool isOneOf(TokenKind K1, TokenKind K2, Ts... Ks) const {
    // expands template down until only 2 token kinds are left
    return is(K1) || isOneOf(K2, Ks...);
  }
};

/// @brief Lexer class
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
