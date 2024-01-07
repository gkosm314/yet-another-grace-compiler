#include "ast.hpp"

extern int yylineno;

/* Maps the mangled name of each variable to the corresponding llvmAddr */
std::map<std::string, llvmAddr> varMap;

AST::AST() : lineno(yylineno) {};

void AST::semError(const char *msg)
{
  fprintf(stderr, "Error: %s at line %d\n", msg, lineno);
  exit(1);
}