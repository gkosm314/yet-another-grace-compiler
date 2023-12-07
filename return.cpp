#include "return.hpp"
#include "ast.hpp"
#include "lexer.hpp"
#include "symbol.h"

Return::Return(Expr *e) : expr(e) {}

Return::~Return() { 
  delete expr;
}

void Return::printAST(std::ostream &out) const {
  out << "Return(";
  if (expr != nullptr)
  {
    out << ", ";
    out << *expr;
  }
  out << ")";
}

void Return::sem()
{
  /* This is a reference to a stack object that will be popped
   * at the end of the function definition. We should not store it. */  
  Type expected_ret_type = ret_types_stack.back();
  
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