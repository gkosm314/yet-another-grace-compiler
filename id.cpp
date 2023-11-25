#include "id.hpp"

Id::Id(std::string s) : str(s) {}

void Id::printAST(std::ostream &out) const {
  out << "Id: " << str;
}