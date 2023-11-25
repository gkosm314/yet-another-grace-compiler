#include "assign.hpp"

Assign::Assign(AbstractLvalue *l, Expr *e) : lval(l), expr(e) {}

Assign::~Assign() { delete lval; delete expr; }

void Assign::printAST(std::ostream &out) const {
  out << *lval << " <- " << *expr;
}