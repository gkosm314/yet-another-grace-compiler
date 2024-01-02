#include "unaryop.hpp"
#include "symbol.h"

UnaryOp::UnaryOp(char o, Expr *e) : expr(e), op(o) {}

UnaryOp::~UnaryOp() { delete expr; }

void UnaryOp::printAST(std::ostream &out) const {
  out << op << "(" << *expr << ")";
}

void UnaryOp::sem()
{
  expr->type_check(typeInteger);
  expr_type = typeInteger;
}

llvm::Value* UnaryOp::compile() {
  llvm::Value *L = expr->compile();
  switch (op) {
    case '+':
      return L;
    case '-':
      return Builder.CreateNeg(L, "unarytemp");
    default:
      return nullptr;
    return nullptr;
  } 
}