#include "header.hpp"

Header::Header(Id *i, std::vector<FParDef *> *vec_defs, DATA_TYPE dt) : id(i), fpar_defs(vec_defs), ret_type(dt) {} ;

Header::~Header() {
  delete id;
  for (FParDef *f: *fpar_defs) delete f;
  delete fpar_defs;
}

void Header::printAST(std::ostream &out) const {
  out << "Header(";
  out << *id;
  out << "FParDefs(";
  bool first = true;
  for (const auto &s : *fpar_defs) {
    if (!first) out << ", ";
    first = false;
    out << *s;
  }
  
  out << ") : ";
  switch (ret_type)
  {
    case DATA_TYPE_int:
      out << "int";
      break;
    case DATA_TYPE_char:
      out << "char";
      break;
    case DATA_TYPE_nothing:
      out << "nothing";
      break;
    default:
      exit(1); /* Will never be reached */
      break;
  }
  out << ")";
}