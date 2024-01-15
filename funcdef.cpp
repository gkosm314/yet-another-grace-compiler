#include "funcdef.hpp"

FuncDef::FuncDef(Header *h,  std::vector<LocalDef *> *vector_def, Block *b) : header(h), local_defs(vector_def), block(b) {} ;

FuncDef::~FuncDef() {
  delete header;
  for (LocalDef *l: *local_defs) delete l;
  delete local_defs;
  delete block;
}

void FuncDef::printAST(std::ostream &out) const {
  out << "FuncDef(";
  out << *header;
  out << "LocalDefs(";
  bool first = true;
  for (const auto &s : *local_defs) {
    if (!first) out << ", ";
    first = false;
    out << *s;
  }
  out << ") : ";
  out << *block;
  out << ")";
}

void FuncDef::hasProgramSignature()
{
  if(header->getParametersCount() != 0) semError("Program cannot take parameters");
  if(!equalType(header->getReturnType(), typeVoid)) semError("Program must be of type nothing");
}

void FuncDef::sem()
{
  /* Perform semantic analysis for function definition */
  header->sem();
  for (LocalDef *i : *local_defs) i->sem();
  block->sem();

  /* If the function has non-void return type it must include a return statement */
  if(equalType(header->getReturnType(), typeInteger) || equalType(header->getReturnType(), typeChar))
  {
    /* Note: We should do this check after calling header->sem() and before calling .pop() on the stack */
    if(!return_stack.returnFound()) semError("Non-void function should have return statement.");
  }

  /* The new scope is opened inside header->sem() */
  return_stack.pop();
  closeScope();
}


llvm::Function* FuncDef::compile()
{
  /* Header */
  std::string mangled_name = header->getMangledName();
  llvm::Function *f = header->compile();

  if (!f)
    return nullptr;

  llvm::BasicBlock *BB = llvm::BasicBlock::Create(TheContext, "entry", f);
  Builder.SetInsertPoint(BB);

  /* Allocate memory for function arguments */
  unsigned int             current_arg         = 0;
  std::vector<std::string> mangled_param_names = header->getParamMangledNames();
  std::vector<llvmType*>   param_types         = header->getParamLLVMTypes();
  for (auto &arg : f->args())
  {
    /* Create alloca instruction for the argument */
    llvmAddr alloca = Builder.CreateAlloca(param_types[current_arg], nullptr, mangled_param_names[current_arg]);  
    /* Initialize argument with the passed parameter */
    Builder.CreateStore(&arg, alloca);
    /* Add argument to the variable map */
    varMap[mangled_param_names[current_arg++]] = alloca;
  }

  /* Allocate memory for local variables and compile local functions */
  for (LocalDef *i : *local_defs)
  {
    i->compile();
    /* We want to continue inserting code inside the current function */
    Builder.SetInsertPoint(BB);
  }

  /* Compile body */
  block->compile();
  
  /* If the exit basic block does not have a return statement at the end, add one */
  if(!Builder.GetInsertBlock()->getTerminator())
  {
    if(equalType(header->getReturnType(), typeInteger) || equalType(header->getReturnType(), typeChar))
      Builder.CreateRet(c64(0));
    else
      Builder.CreateRetVoid();
  }

  llvm::verifyFunction(*f);
  return f;
}