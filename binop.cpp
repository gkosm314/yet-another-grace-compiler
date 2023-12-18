#include "binop.hpp"
#include "symbol.h"

BinOp::BinOp(Expr *l, char o, Expr *r): left(l), op(o), right(r) {}

BinOp::~BinOp() { delete left; delete right; }

void BinOp::printAST(std::ostream &out) const {
  out << op << "(" << *left << ", " << *right << ")";
}

void BinOp::sem()
{
  left->type_check(typeInteger);
  right->type_check(typeInteger);

  expr_type = typeInteger;
}

llvm::Value* BinOp::compile() {
  llvm::Value *L = left->compile();
  llvm::Value *R = right->compile();
  if (!L || !R)
    return nullptr;
  switch (op) {
    case '+':
      return Builder.CreateAdd(L, R, "addtmp");
    case '-':
      return Builder.CreateSub(L, R, "subtmp");
    case '*':
      return Builder.CreateMul(L, R, "multmp");
    case '/':
      return Builder.CreateSDiv(L, R, "divtmp");
    case '%':
      return Builder.CreateSRem(L, R, "modtmp");
    default:
      return nullptr;
    return nullptr;
  }
}