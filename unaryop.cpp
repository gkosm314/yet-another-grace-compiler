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