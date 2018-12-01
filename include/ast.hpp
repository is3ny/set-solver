#ifndef AST_HPP
#define AST_HPP

#include "Token.hpp"
#include <vector>

namespace ast {

#define DEBUG_OUTPUT false

struct node {
  node *left, *right;

  node() : left(nullptr), right(nullptr) {}

  node(node *left, node *right) : left(left), right(right) {}

  virtual bool calc(std::vector<bool> &index) {}
};

class NodeSet : public node {
public:
  NodeSet(char name) : name(name) {}

  bool calc(std::vector<bool> &index) override;

  char getName();

private:
  char name;
};

class NodeUnite : public node {
public:
  NodeUnite(node *left, node *right) : node(left, right) {}

  bool calc(std::vector<bool> &index) override;
};

class NodeIntersect : public node {
public:
  NodeIntersect(node *left, node *right) : node(left, right) {}

  bool calc(std::vector<bool> &index) override;
};

class NodeDiff : public node {
public:
  NodeDiff(node *left, node *right) : node(left, right) {}

  bool calc(std::vector<bool> &index) override;
};

class NodeSym : public node {
public:
  NodeSym(node *left, node *right) : node(left, right) {}

  bool calc(std::vector<bool> &index) override;
};

/*
 * ...
*/

node *allocBin(TokenType type, node *left, node *right);

}
#endif
