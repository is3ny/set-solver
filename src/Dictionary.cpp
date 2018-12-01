#include "../include/Dictionary.hpp"
#include <cstring>

dict::node::node(TokenType type) : type(type) {
    memset(next, 0, sizeof(int) * 256);
}



Dictionary::Dictionary() {
    tree.emplace_back();
}

void Dictionary::add(std::string s, TokenType type) {
    size_t v = 0, i = 0;
    // Propagating the prefix tree
    while (i < s.size()) {
        if (!tree[v].next[s[i]]) {
            tree.emplace_back();
            tree[v].next[s[i]] = tree.size() - 1;
        }
        v = tree[v].next[s[i]];
        ++i;
    }

    // Mark last node as terminal
    tree[v].type = type;
}

TokenType Dictionary::find(std::string s) {
    size_t v = 0, i = 0;
    while (i < s.size()) {
        if (!tree[v].next[s[i]])
            return TOKEN_BAD;
        v = tree[v].next[s[i]];
        ++i;
    }

    return tree[v].type;
}
