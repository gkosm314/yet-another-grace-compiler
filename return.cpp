#include "return.hpp"
#include "ast.hpp"
#include "lexer.hpp"
#include "symbol.h"

Return::Return(DATA_TYPE parsed_ret_type, Expr *e) : expr(e) {
  /* parsed_ret_type is obtained through ret_types_stack.back()
   * This means that it is a reference to a stack object that will be popped
   * at the end of the function definition. We should not store it.
   */
  switch (parsed_ret_type) {
    case DATA_TYPE_int:
      expected_ret_type = typeInteger;
      break;
    case DATA_TYPE_char:
      expected_ret_type = typeChar;
      break;
    case DATA_TYPE_nothing:
      expected_ret_type = typeVoid;
      break;
    default:
      yyerror("Invalid parsed_ret_type passed to Return() constructor");
  }
}

Return::~Return() { delete expr; }

void Return::printAST(std::ostream &out) const {
  out << "Return(";
  out << expected_ret_type;
  if (expr != nullptr)
  {
    out << ", ";
    out << *expr;
  }
  out << ")";
}

void Return::sem()
{
  if(equalType(expected_ret_type, typeVoid))
  {
    if(expr != nullptr) yyerror("Return did not expect an expression");
  }
  else if(equalType(expected_ret_type, typeInteger) || equalType(expected_ret_type, typeChar))
  {
    if(expr != nullptr) expr->type_check(expected_ret_type);
    else yyerror("Return expected an expression");
  }
  // We should never reach this point
  else yyerror("Return has bad expected_ret_type - execution should never reach this point!");
}