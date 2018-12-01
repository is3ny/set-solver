//
// Created by isabelle on 12/1/18 10:05 PM.
//

#ifndef SET_SOLVER_CHECKER_HPP
#define SET_SOLVER_CHECKER_HPP

#include "ast.hpp"
#include <string>
#include <vector>

class Checker {
public:
  Checker(ast::node *set1, ast::node *set2);

  void printTruthTable();
  bool areEqual();

private:
  ast::node *set1, *set2;
  std::string common_sets;
  std::vector<int32_t> tt1, tt2;
  bool equal;

  void set_bit(std::vector<int32_t> &bits, size_t index, bool set);
  int get_bit(std::vector<int32_t> &bits, size_t index);
  std::string find_dependencies(ast::node *tree);
  std::string merge(std::string str1, std::string str2);
  std::vector<bool> gen_index(size_t prmt);
  std::string bin2str(int n, int length = 0);
  void mangle(size_t index, size_t *pos, int *mask);
};

#endif //SET_SOLVER_CHECKER_HPP
