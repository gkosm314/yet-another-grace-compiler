#include "logicalcond.hpp"

LogicalCond::LogicalCond(Condition *l, char o, Condition *r = nullptr): c1(l), op(o), c2(r) {}

LogicalCond::~LogicalCond() { delete c1; delete c2; }

void LogicalCond::printAST(std::ostream &out) const {
  out << op << "(" << *c1;
  if (c2 != nullptr)
    out << ", " << *c2 << ")";
}