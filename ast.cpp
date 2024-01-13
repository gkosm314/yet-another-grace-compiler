#include "ast.hpp"

#include <set>

extern int yylineno;

/* Maps the mangled name of each variable to the corresponding llvmAddr */
/* TODO: rename to allocaMap */
std::map<std::string, llvmAddr> varMap;

/* This set contains the mangled names of variables that are escape variables.
 * In other words, this set contains the mangled names of variables that are used in a nested scope.
 * Mangled names are unique accross the whole program -> no ambiguity.
 */
std::set<std::string> escapeVars;

/* Maps every (non-toplevel) function to the function that defines it
 * Both the key and the value are mangled function names that uniquely identify each function 
 */
std::map<std::string, std::string> outerFunc;

AST::AST() : lineno(yylineno) {};

void AST::semError(const char *msg)
{
  fprintf(stderr, "Error: %s at line %d\n", msg, lineno);
  exit(1);
}