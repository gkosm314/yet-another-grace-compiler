#include "numericcond.hpp"

NumericCond::NumericCond(Expr *l, char o, Expr *r) : left(l), op(o), right(r) {}

NumericCond::~NumericCond() { delete left; delete right; }

void NumericCond::printAST(std::ostream &out) const {
  out << op << "(" << *left << ", " << *right << ")";
}

void NumericCond::sem()
{
  if (check_assignable_operands(left, right)) expr_type = typeBoolean;
  else semError("Type mismatch (numeric cond)");
}

llvm::Value* NumericCond::compile() {
    llvm::Value *L = left->compile();
    llvm::Value *R = right->compile();

    if (!L || !R)
      return nullptr;
    
    switch (op) {
      case '<':
        return Builder.CreateICmpSLT(L, R, "cmplttmp");
      case '>':
        return Builder.CreateICmpSGT(L, R, "cmpgttmp");
      case '#':
        return Builder.CreateICmpNE(L, R, "cmpnetmp");
      case '=':
        return Builder.CreateICmpEQ(L, R, "cmpeqtmp");
      case 'l':
        return Builder.CreateICmpSLE(L, R, "cmpletmp");
      case 'g':
        return Builder.CreateICmpSGE(L, R, "cmpgetmp");
      default:
        return nullptr;
      return nullptr;
    }  
}