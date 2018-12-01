#include "Parser.hpp"

#include <algorithm>

static const int CONTEXT_LEN = 3;

Parser::Parser(std::string exp) : ok(true) {
    this->exp = "(" + exp + ")";
    ops.add("&", TOKEN_INTERSECTION);
    ops.add("|", TOKEN_UNION);
    ops.add("/", TOKEN_DIFFERENCE);
    ops.add("^", TOKEN_SYMDIFFERENCE);
}

bool Parser::isOK() {
    return ok;
}

std::string Parser::getMessage() {
    return msg;
}

// Parsing follows this set of simple rules
// * Operators do not contain numbers and brackets
// * Numbers contain only digits ['0'..'9']
// Thus we can easily distinct numbers from operators
bool Parser::tokenize() {
    // Parsing invariant:
    // Everything before [i] was tokenized
    for (size_t i = 0; i < exp.size(); ++i) {
        Token token;
        if ('A' <= exp[i] && exp[i] <= 'Z')
            token = parseSet(i);
        else if (exp[i] == '(')
            token = Token(TOKEN_OPENING_BRACKET);
        else if (exp[i] == ')')
            token = Token(TOKEN_ENCLOSING_BRACKET);
        else
            token = parseOperator(i);

        if (!ok)
            return false;
        
        tokens.push_back(token);
    }
    return true;
}

Token Parser::parseSet(size_t &i) {
    return {TOKEN_SET, exp[i]};
}

Token Parser::parseOperator(size_t &i) {
    // Accumulate operator until digit, '(' or ')' is found
    std::string op;
    while (i < exp.size() && 
           (exp[i] < 'A' || 'Z' < exp[i]) &&
           exp[i] != '(' && exp[i] != ')') {
        op.push_back(exp[i]);
        ++i;
    }

    TokenType token = ops.find(op);
    
    // Handle ERROR
    // TODO: Use extract() instead
    if (token == TOKEN_BAD) {
        ok = false;
        char *msg_raw = (char *)malloc(sizeof(char) * 256);
        sprintf(msg_raw, "ERROR: Unknown operator \'%s\' at %d (%s)",
                op.c_str(), i - op.size() + 1, 
                exp.substr(std::max((size_t)2, i - op.size() - CONTEXT_LEN + 1),
                           std::min((size_t)exp.size() - 2,
                                    op.size() + 2 * CONTEXT_LEN)).c_str());
        msg = std::string(msg_raw);
    }

    --i;  // Follow parsing invariant
    return token;
}

ast::node* Parser::generate() {
    std::vector<std::pair<TokenType, int>> acts;
    std::vector<ast::node *> trees;
    size_t size_trees = 0, size_acts = 0;
    
    for (auto token : tokens) {
        if (token.type == TOKEN_SET) {
            if (size_trees >= trees.size())
                trees.push_back(nullptr);
            trees[size_trees++] = new ast::NodeSet(token.name);
            continue;
        }

        // Add new operation on stack
        if (size_acts >= acts.size())
            acts.emplace_back();
        acts[size_acts++] = {token.type, precedence[token.type]};
        
        // We should pop all operators whose precedence is smaller than of the
        // current one, in order to guarantee the correctness of the AST.
        while (acts[size_acts - 1].first != TOKEN_OPENING_BRACKET &&
                size_acts > 1 &&
                acts[size_acts - 2].second <= acts[size_acts - 1].second) {
            if (size_trees < 2) {
                ok = false, msg = "ERROR: Operator balance discrepancy";
                return nullptr;
            }     
            // Binary operation: get two trees from stack
            // And push new one
            ast::node *n = ast::allocBin(acts[size_acts - 2].first,
                    trees[size_trees - 2], trees[size_trees - 1]);
            trees[--size_trees - 1] = n;

            // Wipe committed operator
            acts[size_acts - 2] = acts[size_acts - 1];
            --size_acts;
        }

        if (size_acts == 1 && acts[0].first == TOKEN_ENCLOSING_BRACKET) {
            ok = false, msg = "ERROR: Brace balance discrepancy";
            return nullptr;
        }

        // Pop pair of brackets
        if (acts[size_acts - 1].first == TOKEN_ENCLOSING_BRACKET)
            size_acts -= 2;      
    }

    if (size_acts > 0) {
      ok = false, msg = "ERROR: Brace balance discrepancy";
      return nullptr;
    }

    if (size_trees == 0) {
        ok = false, msg = "ERROR: Empty expression";
        return nullptr;
    }

    return trees[0];
}

