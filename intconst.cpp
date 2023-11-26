#include "intconst.hpp"
#include "symbol.h"

IntConst::IntConst(int v) : val(v) {}

void IntConst::printAST(std::ostream &out) const {
  out << "IntConst(" << val << ")";
}

void IntConst::sem()
{
  expr_type = typeInteger;
}