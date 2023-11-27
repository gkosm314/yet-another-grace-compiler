#include "id.hpp"

Id::Id(std::string s) : name(s) {}

void Id::printAST(std::ostream &out) const {
  out << "Id: " << name;
}

const char * Id::getName() const {
  /* Return std::string name as (const char *) */
  return name.c_str();
}