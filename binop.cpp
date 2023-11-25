#include "binop.hpp"

BinOp::BinOp(Expr *l, char o, Expr *r): left(l), op(o), right(r) {}

BinOp::~BinOp() { delete left; delete right; }

void BinOp::printAST(std::ostream &out) const {
  out << op << "(" << *left << ", " << *right << ")";
}