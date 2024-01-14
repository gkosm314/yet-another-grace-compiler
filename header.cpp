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

  /* Keep function's nesting level */
  funcDepth[mangled_name] = f->nestingLevel;

  /* In case of multiple forward declarations using the same signature, we will set f->isForward to true again
   * This means that those declarations are allowed, since the check on newFunction() on symbol.c will accept them
   * This is a decision made by us that doesn't contradict with the language specification
   */
  if(isForward)
    forwardFunction(f);

  openScope();

  /* Keep return type */
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
  if(!isTopLevelFunc(mangled_name))
    pushStaticLinkForStackFrameStruct(&mangled_param_names, &param_types);

  /* Get function arguments types and mangled names */
  /* Each call to the compile method of the parameter pushes its type and its mangled name
   * to the vector that are passed by reference. The types vector is used to create the function signature */
  for (FParDef *p: *fpar_defs)
    p->compile(&mangled_param_names, &param_types);

  /* Check whether function f has already been created due to forward declaration */
  llvm::Function *f = TheModule->getFunction(mangled_name);
  if (!f)
  {
    /* Get function return type */
    llvmType *rt = getLLVMType(ret_type);
    /* Make the function type - example: void(int,char) */
    llvm::FunctionType *ft = llvm::FunctionType::get(rt, param_types, false);
    /* Create function */
    f = llvm::Function::Create(ft, llvm::Function::ExternalLinkage, mangled_name, TheModule.get()); 
  }

  return f;
}

std::string Header::getMangledName()
{
  return mangled_name;
}

std::vector<llvmType*> Header::getParamLLVMTypes()
{
  return param_types;
}

std::vector<std::string> Header::getParamMangledNames()
{
  return mangled_param_names;
}

void Header::pushStaticLinkForStackFrameStruct(std::vector<std::string> *names, std::vector<llvmType*> *types)
{
  /* Get the name of the function that encapsulated this function (outer function) */
  std::string outer_func_mangled_name = outerFunc[mangled_name];
  /* Get the name of the struct that represent the stack frame of the outer function */
  std::string outer_func_stack_frame_struct_name = getStackFrameStructName(outer_func_mangled_name);
  /* Get the type of the struct that represent the stack frame of the outer function and push it in the function's signature */
  types->push_back(llvm::StructType::getTypeByName(TheContext, outer_func_stack_frame_struct_name)->getPointerTo());
  /* Push the name of the static link variable in the names struct */
  names->push_back("static_link_" + mangled_name);
}

void Header::pushFieldsForStackFrameStruct(std::vector<std::string> *names, std::vector<llvmType*> *types, std::vector<bool> *isref)
{
  for (FParDef *p: *fpar_defs)
    p->pushFieldsForStackFrameStruct(names, types, isref);
}