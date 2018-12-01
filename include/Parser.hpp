/* Parser class is used to generate tokens from expression and to consequently generate an AST
 * 
*/

#ifndef PARSER_HPP
#define PARSER_HPP

#include "ast.hpp"
#include "Dictionary.hpp"
#include "Token.hpp"

#include <string>
#include <vector>

class Parser {
public:
    Parser(std::string exp);

    bool tokenize();
    ast::node* generate();
    std::string getMessage();
    bool isOK();

private:
    std::string exp;
    std::vector<Token> tokens;    
    bool ok;
    std::string msg;
    Dictionary ops;

    Token parseSet(size_t &i);
    Token parseOperator(size_t &i);
};

#endif
