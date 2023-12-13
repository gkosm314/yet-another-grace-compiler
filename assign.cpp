#include "assign.hpp"

Assign::Assign(AbstractLvalue *l, Expr *e) : lval(l), expr(e) {}

Assign::~Assign() { delete lval; delete expr; }

void Assign::printAST(std::ostream &out) const {
  out << *lval << " <- " << *expr;
}

void Assign::sem()
{
  /* We check that lval is not a function inside lval->sem() */
  if (!check_assignable_operands(lval, expr)) semError("Bad types (assign)");
  /* If the function has already returned we should not generate code */
  checkIfStmtIsAfterReturn();
}