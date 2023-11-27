#include "vardef.hpp"

VarDef::VarDef(std::vector<Id *> *ids_vec, ParsedType *t ) : ids(ids_vec), parsed_type(t)
{
  var_type = toType(t);
};

VarDef::~VarDef() {
  for (Id *i : *ids) delete i;
  delete parsed_type;
  if(var_type) destroyType(var_type);
  delete ids;
}

void VarDef::printAST(std::ostream &out) const {
  out << "VarDef(";
  out << var_type;
  out << "Ids: (";
  bool first = true;
  for (const auto &s : *ids) {
    if (!first) out << ", ";
    first = false;
    out << *s;
  }
  out << ")";
}

void VarDef::sem()
{
  /* Iterate over the ids of the vars that we want to define */
  for(Id* id : *ids)
    /* Add variable to the symbol table */
    newVariable(id->getName(), var_type);
}