#include "intconst.hpp"

IntConst::IntConst(int v) : val(v) {}

void IntConst::printAST(std::ostream &out) const {
  out << "IntConst(" << val << ")";
}