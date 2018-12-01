/* main.cpp
 * Isabelle Lightray 2018-12-01 16:39
 */

#include "../include/Parser.hpp"
#include "../include/Checker.hpp"

#include <cstdio>
#include <string>

void printHelpMessage();

int main(int argc, char *argv[]) {
  if (argc != 3) {
    puts("Invalid arguments\n");
    printHelpMessage();
    return 0;
  }

  // TODO: Error messages mention the flawed set
  // TODO: Complement operator !

  auto *parser = new Parser(std::string(argv[1]));
  if (!parser->tokenize()) {
    puts(parser->getMessage().c_str());
    return -1;
  }

  ast::node *set1 = parser->generate();
  if (set1 == nullptr) {
    puts(parser->getMessage().c_str());
    return -2;
  }

  delete parser;
  parser = new Parser(std::string(argv[2]));
  if (!parser->tokenize()) {
    puts(parser->getMessage().c_str());
    return -3;
  }

  ast::node *set2 = parser->generate();
  if (set2 == nullptr) {
    puts(parser->getMessage().c_str());
    return -4;
  }

  auto *checker = new Checker(set1, set2);
  checker->printTruthTable();
  if (checker->areEqual()) {
    puts("EQUAL\n");
  } else {
    puts("UNEQUAL\n");
  }

  return 0;
}

void printHelpMessage() {
  puts("Usage: set-solver [expression1] [expression2]\n");
  puts("Expression is a representation of a set in terms of other \"basic\" "
       "sets any element can or can be not part of.\n"
       "Given two sets expressed like this we can check for two sets' "
       "equivalence.\n");
  puts("BNF of an expression:\n"
       "<set> ::= <var> | <set> <op> <set> | '(' <set> <op> <set> ')'\n"
       "<var> ::= ('A'-'Z')\n"
       "<op>  ::= \"&\" | \"|\" | \"/\" | \"^\"\n");
  puts("The available \"basic\" sets are represented by capital latin letters\n"
       "The available operators are\n"
       "\t&\tIntersection between two sets\n"
       "\t|\tUnion of two sets\n"
       "\t/\tDifference between two sets\n"
       "\t^\tSymmetric difference between two sets\n"
       "all having the same precedence.");
}