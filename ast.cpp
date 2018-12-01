#include "ast.hpp"
#include <cstdio>

namespace ast {

bool NodeSet::calc(std::vector<bool> &index) {
  if (DEBUG_OUTPUT)
    printf("%c : %d\n", name, (int)index[name - 'A']);
  return index[name - 'A'];
}

char NodeSet::getName() {
  return name;
}

bool NodeUnite::calc(std::vector<bool> &index) {
  return left->calc(index) | right->calc(index);
}

bool NodeIntersect::calc(std::vector<bool> &index) {
  return left->calc(index) & right->calc(index);
}

bool NodeDiff::calc(std::vector<bool> &index) {
  return left->calc(index) & !right->calc(index);
}

bool NodeSym::calc(std::vector<bool> &index) {
  return left->calc(index) ^ right->calc(index);
}

node * allocBin(TokenType type, node *left, node *right) {
    switch (type) {
      case TOKEN_UNION:
        return new NodeUnite(left, right);
      case TOKEN_INTERSECTION:
        return new NodeIntersect(left, right);
      case TOKEN_DIFFERENCE:
        return new NodeDiff(left, right);
      case TOKEN_SYMDIFFERENCE:
        return new NodeSym(left, right);
      default:
        return nullptr;
    }
}

}