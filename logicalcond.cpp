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

llvm::Value* LogicalCond::compile() {
  llvm::Value *L = c1->compile();
  llvm::Value *R;

  if (!L)
    return nullptr;
  
  if (c2 != nullptr) {
    R = c2->compile();
    if (!R)
      return nullptr;
  }
  
  switch (op) {
    case 'n':
      return Builder.CreateNot(L, "logicalnottemp");
    case 'a':
      return Builder.CreateAnd(L, R, "logicalandtemp");
    case 'o':
      return Builder.CreateOr(L, R, "logicalortemp");
    default:
      return nullptr;
    return nullptr;
  } 
}