#include "unaryop.hpp"

UnaryOp::UnaryOp(char o, Expr *e) : expr(e), op(o) {}

UnaryOp::~UnaryOp() { delete expr; }

void UnaryOp::printAST(std::ostream &out) const {
  out << op << "(" << *expr << ")";
}