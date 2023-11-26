#include "logicalcond.hpp"
#include "symbol.h"

LogicalCond::LogicalCond(Condition *l, char o, Condition *r): c1(l), op(o), c2(r) {}

LogicalCond::~LogicalCond() { delete c1; delete c2; }

void LogicalCond::printAST(std::ostream &out) const {
  out << op << "(" << *c1;
  if (c2 != nullptr)
    out << ", " << *c2 << ")";
}

void LogicalCond::sem()
{
  c1->type_check(typeBoolean);
  c2->type_check(typeBoolean);

  expr_type = typeBoolean;
}