#include "charconst.hpp"

CharConst::CharConst(char c) : val(c) {}

void CharConst::printAST(std::ostream &out) const {
  out << "CharConst(" << val << ")";
}

void CharConst::sem()
{
  expr_type = typeChar;
}