#include "ast.hpp"

extern int yylineno;

AST::AST() : lineno(yylineno) {};

void AST::semError(const char *msg)
{
  fprintf(stderr, "Error: %s at line %d\n", msg, lineno);
  exit(1);
}