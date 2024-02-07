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

void VarDef::pushFieldsForStackFrameStruct(std::vector<std::string> *names, std::vector<llvmType*> *types, std::vector<bool> *isref)
{
  /* The stack frame only contains references to the variables */
  llvmType* t = llvm::PointerType::get(getLLVMType(var_type), 0);

  for (auto &mangled_name : mangled_names)
  {
    /* If the variable is an escape variable, add a field to store it in the stack frame */
    if(escapeVars.find(mangled_name) != escapeVars.end())
    {
      names->push_back(mangled_name);
      types->push_back(t);
      
      /* variables defined in this function are never pointers */
      isref->push_back(false);
      
      /* keep the pos of the variable inside the stack frame so that you know where to look for it
       * the position of the variable is the position of the type you just push_backed */
      stackframePos[mangled_name] = types->size() - 1;
    }
  }  
}