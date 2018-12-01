#ifndef DICTIONARY_HPP
#define DICTIONARY_HPP

#include "Token.hpp"

#include <string>
#include <vector>

namespace dict {

struct node {
    TokenType type;
    size_t next[256];

    node(TokenType type = TOKEN_BAD);
};

}  // End of dict

class Dictionary {
public:
    Dictionary();
    void add(std::string s, TokenType type);
    TokenType find(std::string s);
private:
    std::vector<dict::node> tree;
};

#endif
