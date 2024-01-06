#include "fpardef.hpp"

FParDef::FParDef(std::vector<Id *> *ids_vec, ParsedType *f, bool ref) : ids(ids_vec), param_parsed_type(f)
{
  if(ref) pass_mode = PASS_BY_REFERENCE;
  else    pass_mode = PASS_BY_VALUE;

  param_type = toType(param_parsed_type);
}

FParDef::~FParDef() {
  for (Id *i : *ids) delete i;
  delete param_parsed_type;
  if(param_type) destroyType(param_type);
  delete ids;
}

void FParDef::printAST(std::ostream &out) const {
  out << "FParDef(";
  if (pass_mode == PASS_BY_REFERENCE) out << "ref:";
  out << "Ids(";
  bool first = true;
  for (const auto &s : *ids) {
    if (!first) out << ", ";
    first = false;
    out << *s;
  }
  out << ") : ";
  out << param_type;
  out << ")";
}

void FParDef::setFunction(SymbolEntry *e)
{
  f = e;
}

void FParDef::sem()
{
  /* Arrays passed as function parameters can be passed by reference only */
  bool isArrayType = !equalType(param_type, typeInteger) && !equalType(param_type, typeChar);
  if(isArrayType && pass_mode != PASS_BY_REFERENCE)
  {
    semError("Arrays can only be passed by reference.");
  }

  /* Iterate over the ids of the params that we want to define */
  SymbolEntry *e;
  for(Id* id : *ids)
  {
    /* Add parameter to the symbol table */
    e = newParameter(id->getName(), param_type, pass_mode, f);
  }

  /* Keep scope_id to use for name mangling */
  scope_id = e->scopeId;

  /* The entry to which f pointed will be deleted once closeScope() is called.
     As a result, f should not be used after FParDef::sem() is completed. */
  f = nullptr;
}

llvm::Value* FParDef::compile()
{
  /* Execution should never reach this point */
  semError("Problem: FParDef::compile() should never be called without arguments!");
  exit(1);
  return nullptr;
}

llvm::Value* FParDef::compile(std::vector<std::string> * signature_mangled_names, std::vector<llvmType*> * signature_types)
{
  /* Get LLVM type of argument */
  /* TODO: this works only with simple types */
  llvmType* t = getLLVMType(param_type);

  /* Create function arguments signature and store the mangled names of the arguments */
  /* We push the types and the mangled names to the vectors that are passed by the reference */
  for (Id *id : *ids)
  {
    signature_types->push_back(t);
    signature_mangled_names->push_back(mangle(id->getName(), scope_id));
  }

  return nullptr;
}