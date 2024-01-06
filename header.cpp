#include "header.hpp"

Header::Header(Id *i, std::vector<FParDef *> *vec_defs, DATA_TYPE dt) : id(i), fpar_defs(vec_defs)
{
  ret_type = toType(dt);
}

Header::~Header() {
  delete id;
  for (FParDef *f: *fpar_defs) delete f;
  delete fpar_defs;

  if(ret_type) destroyType(ret_type);
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
  out << ret_type;
  out << ")";
}

size_t Header::getParametersCount()
{
  return fpar_defs->size();
}

Type Header::getReturnType()
{
  return ret_type;
}

void Header::setForward()
{
  isForward = true;
}

void Header::sem()
{
  SymbolEntry *f = newFunction(id->getName());

  /* Store mangled name */
  mangled_name = mangle(id->getName(), f->scopeId);
  /* Store scope id to use for fpardef name mangling */
  scope_id = f->scopeId;

  /* In case of multiple forward declarations using the same signature, we will set f->isForward to true again
   * This means that those declarations are allowed, since the check on newFunction() on symbol.c will accept them
   * This is a decision made by us that doesn't contradict with the language specification
   */
  if(isForward)
    forwardFunction(f);

  openScope();
  return_stack.push(ret_type);

  for (FParDef *p : *fpar_defs)
  {
    p->setFunction(f);
    p->sem();
  }
  endFunctionHeader(f, ret_type);
  
  /* The scope is closed by FuncDecl or FuncDef, because
     FuncDef needs to add local definitions in the same scope*/
}

llvm::Function* Header::compile()
{
  /* Get function arguments types and mangled names */
  std::vector<llvmType*>   arg_types;
  std::vector<std::string> mangled_param_names;

  for (FParDef *i: *fpar_defs)
  {
    /* Get LLVM type of argument */
    llvmType* t = getLLVMType(i->getType());
    std::vector<Id*> fpardef_ids = *(i->getIds());

    /* Create function arguments signature and store mangled names for the arguments */
    for (int j=0; j < fpardef_ids.size(); j++)
    {
      arg_types.push_back(t);
      mangled_param_names.push_back(mangle(fpardef_ids[j]->getName(), scope_id));
    }
  }

  /* TODO: add parameters to llvm symbol table */

  /* Get function return type */
  llvmType *rt = getLLVMType(ret_type);

  /* Make the function type - example: void(int,char) */
  llvm::FunctionType *ft = llvm::FunctionType::get(rt, arg_types, false);

  /* Create function */
  llvm::Function *f = llvm::Function::Create(ft, llvm::Function::ExternalLinkage, mangled_name, TheModule.get());

  /* Set mangled names for the paramters */
  unsigned int current_arg = 0;
  for (auto &arg : f->args())
    arg.setName(mangled_param_names[current_arg++]);

  return f;
}

std::string Header::getMangledName()
{
  return mangled_name;
}
