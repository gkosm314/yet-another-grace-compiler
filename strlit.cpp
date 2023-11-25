#include "strlit.hpp"

StrLit::StrLit(std::string s) : str(s) {}

void StrLit::printAST(std::ostream &out) const {
  out << "StrLit(" << str <<  ")";
}