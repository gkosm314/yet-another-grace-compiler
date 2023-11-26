#include "numericcond.hpp"

NumericCond::NumericCond(Expr *l, char o, Expr *r) : left(l), op(o), right(r) {}

NumericCond::~NumericCond() { delete left; delete right; }

void NumericCond::printAST(std::ostream &out) const {
  out << op << "(" << *left << ", " << *right << ")";
}

void NumericCond::sem()
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

  if (int_operands || char_operands)
  {
    expr_type = typeBoolean;
  }
  else
  {
    yyerror("Type mismatch (numeric cond)");
  }
}