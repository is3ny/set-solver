//
// Created by isabelle on 8/12/18.
//

#ifndef TOKEN_HPP
#define TOKEN_HPP

enum TokenType {                                                       // Preced
  TOKEN_BAD,                                                               // 0
  TOKEN_SET,                                                               // 1
  TOKEN_UNION, TOKEN_INTERSECTION, TOKEN_DIFFERENCE, TOKEN_SYMDIFFERENCE,  // 2
  TOKEN_OPENING_BRACKET, TOKEN_ENCLOSING_BRACKET,                          // MAX
  TOKENTYPE_SIZE                                                           // N/A
};

static int precedence[TOKENTYPE_SIZE] {
        0,
        1,
        2, 2, 2, 2,
        TOKENTYPE_SIZE + 1, TOKENTYPE_SIZE
};

struct Token {
  TokenType type;
  char name;

  Token(TokenType type = TOKEN_BAD, char name = '?') : type(type), name(name) {}
};


#endif