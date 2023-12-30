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
  /*
   * In case of multiple forward declarations using the same signature, we will set f->isForward to true again
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
  /* Make the function type - example: void(int,char) */
  std::vector<llvmType*> arg_types;

  for (FParDef *i: *fpar_defs) {
    llvmType* t = getLLVMType(i->getType()); 
    int idsSize = i->getIds()->size();
    for (int i=0; i<idsSize; i++)
      arg_types.push_back(t);
  }
  llvmType *retType = getLLVMType(ret_type);

  llvm::FunctionType *ft = llvm::FunctionType::get(retType, arg_types, false);



  /* Create Function */
  /* TODO: get mangled name here */
  std::string mangled_name = id->getName();
  llvm::Function *f = llvm::Function::Create(ft, llvm::Function::ExternalLinkage, mangled_name, TheModule.get());

  return f;
}