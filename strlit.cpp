#include "strlit.hpp"
#include "symbol.h"

StrLit::StrLit(std::string s) : str(s) {}

StrLit::~StrLit()
{
  destroyType(expr_type);
}

void StrLit::printAST(std::ostream &out) const {
  out << "StrLit(" << str <<  ")";
}

void StrLit::sem()
{
  /* String literals have type char[n], with n = length_of_string + 1  */
  RepInteger char_array_len = str.length() + 1;
  expr_type = typeArray(char_array_len, typeChar);
}