#include "expr.hpp"

Type Expr::getType()
{
    /* Assumption: sem() or type_check() was called before this is called */
    return expr_type;
}

void Expr::type_check(Type expected_type)
{
    sem();

    if(!equalType(expr_type, expected_type))
    {
        semError("Type mismatch");
    }
}

void Expr::type_check_param(Type expected_type)
{
    sem();

    if(!equalTypeAutocomplete(expr_type, expected_type))
    {
        semError("Type mismatch");
    }
}

bool Expr::isLvalue()
{
    return false;
}

bool check_assignable_operands(Expr *left, Expr *right)
{
  /* Either both operands will be integers or both operands will be chars. */

  /* Semantic analysis for both operands */
  left->sem();
  right->sem();

  /* Grab type of both operands */
  Type left_type  = left->getType();
  Type right_type = right->getType();

  /* Check if both operands are of type int or if both operands are of type char */
  bool int_operands  = equalType(left_type,  typeInteger) &&
                       equalType(right_type, typeInteger);
  bool char_operands = equalType(left_type,  typeChar) &&
                       equalType(right_type, typeChar);

  return int_operands || char_operands;
}