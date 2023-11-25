#include "fpardef.hpp"


FParDef::FParDef(std::vector<Id *> *ids_vec, ParsedType *f, bool b) : ids(ids_vec), fpar_type(f), ref(b) {};

FParDef::~FParDef() {
  for (Id *i : *ids) delete i;
  delete fpar_type;
  delete ids;
}

void FParDef::printAST(std::ostream &out) const {
  out << "FParDef(";
  if (ref) out << "ref:";
  out << "Ids(";
  bool first = true;
  for (const auto &s : *ids) {
    if (!first) out << ", ";
    first = false;
    out << *s;
  }
  out << ") : ";
  out << *fpar_type;
  out << ")";
}