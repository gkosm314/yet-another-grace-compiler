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
  for(int i = 0; i < ids->size(); i++)
  {
    const char * var_name = (*ids)[i]->getName();
    /* Add variable to the symbol table */
    SymbolEntry *e = newVariable(var_name, var_type);
    mangled_names.push_back(mangle(var_name, e->scopeId));
  }
}

llvm::Value* VarDef::compile()
{
  /* Get LLVM type of argument */
  llvmType* t = getLLVMType(var_type);

  for(int i = 0; i < ids->size(); i++)
  {
    /* Create alloca instruction */
    llvmAddr alloca = Builder.CreateAlloca(t, nullptr, mangled_names[i]);
    /* Add variable to the variable map */
    varMap[mangled_names[i]] = alloca;
  }

  return nullptr; 
}