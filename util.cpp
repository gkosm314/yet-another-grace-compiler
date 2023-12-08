#include "util.hpp"
#include "lexer.hpp"

/* Use yylineno from lexer file, since the main is in this file we need to use extern here */
extern int yylineno;

std::ostream &operator<<(std::ostream &out, const AST &ast)
{
  ast.printAST(out);
  return out;
}

std::ostream &operator<<(std::ostream &out, const Type &t)
{
  printType(t);
  return out;
}

void yyerror(const char *msg)
{
  fprintf(stderr, "Error: %s at line %d\n", msg, yylineno);
  exit(1);
}

Type toType(DATA_TYPE datatype_arg)
{
  Type t;

  switch (datatype_arg) {
    case DATA_TYPE_int:
      t = typeInteger;
      break;
    case DATA_TYPE_char:
      t = typeChar;
      break;
    case DATA_TYPE_void:
      t = typeVoid;
      break;
    default:
      /* Execution should never reach this point */
      yyerror("Invalid datatype_arg passed in toType()");
      break;
  }  

  return t;
}