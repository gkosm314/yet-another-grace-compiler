#include "vardef.hpp"

VarDef::VarDef(std::vector<Id *> *ids_vec, ParsedType *t ) : ids(ids_vec), type(t) {};

VarDef::~VarDef() {
  for (Id *i : *ids) delete i;
  delete type;
  delete ids;
}

void VarDef::printAST(std::ostream &out) const {
  out << "VarDef(";
  out << *type;
  out << "Ids: (";
  bool first = true;
  for (const auto &s : *ids) {
    if (!first) out << ", ";
    first = false;
    out << *s;
  }
  out << ")";
}