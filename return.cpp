#include "return.hpp"

Return::Return(Expr *e = nullptr) : expr(e) {}

Return::~Return() { delete expr; }

void Return::printAST(std::ostream &out) const {
  out << "Return(";
  if (expr != nullptr)
    out << *expr;
  out << ")";
}