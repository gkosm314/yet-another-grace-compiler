#include "lmatrix.hpp"

LMatrix::LMatrix(AbstractLvalue *lval, Expr *e) : lvalue(lval), expr(e) {}

LMatrix::~LMatrix() { delete lvalue; delete expr; }

void LMatrix::printAST(std::ostream &out) const {
  out << *lvalue;
  out << "[";
  out << *expr;
  out << "]";  
}