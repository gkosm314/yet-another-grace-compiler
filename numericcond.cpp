#include "numericcond.hpp"

NumericCond::NumericCond(Expr *l, char o, Expr *r) : left(l), op(o), right(r) {}

NumericCond::~NumericCond() { delete left; delete right; }

void NumericCond::printAST(std::ostream &out) const {
  out << op << "(" << *left << ", " << *right << ")";
}