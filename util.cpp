#include "util.hpp"
#include "lexer.hpp"

#include <vector>

/* Use yylineno from lexer file, since the main is in this file we need to use extern here */
extern int yylineno;

/* We keep the return types of the function definitions we semantically analyze in this stack,
 * in order to know the expected return type of a return statement when we call semantically analyze it.
 * Using a stack works correctly because function definitions are nested.
 * We push the return type every type we semantically analyze a header,
 * This includes ret_types inside the headers of forward-declared functions (func-decl). 
 * We pop the ret_type from the stack when the definition (or declaration) finishes.
 */
std::vector<Type> ret_types_stack;

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