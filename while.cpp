#include "while.hpp"

While::While(Condition *c, Stmt *s) : cond(c), stmt(s) {}

While::~While() { delete cond; delete stmt; }

void While::printAST(std::ostream &out) const {
  out << "While(" << *cond << "," << *stmt << ")";
}

void While::sem()
{
  cond->type_check(typeBoolean);
  stmt->sem();
}