//
// Created by isabelle on 12/1/18 10:10 PM.
//

#include "Checker.hpp"

Checker::Checker(ast::node *set1, ast::node *set2) : set1(set1), set2(set2)  {
  equal = true;

  std::string basic1 = find_dependencies(set1);
  std::string basic2 = find_dependencies(set2);
  common_sets = merge(basic1, basic2);

  // TODO: Check 1-left error
  tt1.resize((1 << common_sets.size()));
  tt2.resize((1 << common_sets.size()));

  for (size_t prmt = 0; prmt < (1 << common_sets.size()); prmt++) {
    std::vector<bool> index = gen_index(prmt);

    bool res1 = set1->calc(index);
    bool res2 = set2->calc(index);
    set_bit(tt1, prmt, (int)res1);
    set_bit(tt2, prmt, (int)res2);
    if (res1 != res2)
      equal = false;
  }
}

void Checker::printTruthTable() {
  printf("%s\t12\n", common_sets.c_str());
  for (int prmt = 0; prmt < (1 << common_sets.size()); prmt++) {
    int val1 = get_bit(tt1, prmt), val2 = get_bit(tt2, prmt);
    printf("%s\t%c%c %c\n", bin2str(prmt).c_str(), '0' + val1,
            '0' + val2, val1 != val2 ? '*' : ' ');
  }
  puts("");
}

bool Checker::areEqual() {
  return equal;
}

void Checker::set_bit(std::vector<int32_t> &bits, size_t index, bool set) {
  size_t pos;
  int32_t mask;
  mangle(index, &pos, &mask);

  if (!set)
    bits[pos] &= ~mask;
  else
    bits[pos] |= mask;
}

int Checker::get_bit(std::vector<int32_t> &bits, size_t index) {
  size_t pos;
  int32_t mask;
  mangle(index, &pos, &mask);
  return (bits[pos] & mask) >> (index % 32);
}

void Checker::mangle(size_t index, size_t *pos, int *mask) {
  *pos = index >> 5;  // index / 32
  *mask = (1 << (index % 32 ));  // mask = [0] + 1 @ index%32
}

std::string Checker::find_dependencies(ast::node *tree) {
  std::string result;
  if (!tree)
    return result;

  if (!tree->left && !tree->right)
    result.push_back(dynamic_cast<ast::NodeSet *>(tree)->getName());
  else
    result = find_dependencies(tree->left) + find_dependencies(tree->right);

  return result;
}

std::string Checker::merge(std::string str1, std::string str2) {
  // TODO: Replace with bit array
  bool cnt[256];
  for (int i = 0; i < 256; i++)
    cnt[i] = 0;

  for (auto &i : str1)
    cnt[i] = true;
  for (auto &i : str2)
    cnt[i] = true;

  std::string result;
  for (int i = 0; i < 256; i++)
    if (cnt[i])
      result.push_back((char)i);

  return result;
}

std::vector<bool> Checker::gen_index(size_t prmt) {
  std::vector<bool> index('Z' - 'A' + 1, false);
  for (size_t i = 0; i < common_sets.size(); i++) {
    index[common_sets[i] - 'A'] = (bool)((prmt >> i) & 1);
  }

  return index;
}

std::string Checker::bin2str(int n, int length) {
  std::string str(length ? length : common_sets.size(), '0');
  int pos = 0;
  while (n != 0) {
    str[pos++] = (char)('0' + (n & 1));
    n >>= 1;
  }

  return str;
}