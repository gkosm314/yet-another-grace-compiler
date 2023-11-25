#include "if.hpp"

If::If(Condition *c, Stmt *s1, Stmt *s2 = nullptr) : cond(c),  stmt1(s1), stmt2(s2) {}

If::~If() { delete cond; delete stmt1; delete stmt2; }

void If::printAST(std::ostream &out) const {
  out << "If(" << *cond << ", " << *stmt1;
  if (stmt2 != nullptr) out << ", " << *stmt2;
  out << ")";
}