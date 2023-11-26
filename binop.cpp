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
