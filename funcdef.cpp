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

  /* Mark the function as void without a return statement inside its body - we need this for codegen*/
  if(equalType(header->getReturnType(), typeVoid))
    if(!return_stack.returnFound()) void_ret_type_without_ret_stmt = true;

  /* The new scope is opened inside header->sem() */
  return_stack.pop();
  closeScope();
}


llvm::Function* FuncDef::compile()
{
  /* Header */
  std::string mangled_name = header->getMangledName();
  llvm::Function *f = TheModule->getFunction(mangled_name);

  /* f is not nullptr when the header is already compiled due to a forward declaration */
  if (!f)
    f = header->compile();

  if (!f)
    return nullptr;

  llvm::BasicBlock *BB = llvm::BasicBlock::Create(TheContext, "entry", f);
  Builder.SetInsertPoint(BB);

  /* Local defs */
  for (LocalDef *i : *local_defs)
  {
    i->compile();
    /* We want to continue inserting code inside the current function */
    Builder.SetInsertPoint(BB);
  }

  /* Body */
  block->compile();
  
  /* Create return value for void function without return statement inside its body */
  if(void_ret_type_without_ret_stmt)
    Builder.CreateRetVoid();

  llvm::verifyFunction(*f);
  return f;
}