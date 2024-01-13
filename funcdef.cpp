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

  /* Allocate memory for function arguments */
  /* TODO: validate this works okey after we added the static link in the vectors */
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

  /* Create LLVM struct type to represent stack frame of this function.
   * A pointer to this struct type will be passed as the first argument to every function
   * defined inside this FuncDef. 
   */
  generateStackFrameStruct();

  /* Allocate memory for local variables and compile local functions */
  for (LocalDef *i : *local_defs)
  {
    i->compile();
    /* We want to continue inserting code inside the current function */
    Builder.SetInsertPoint(BB);
  }

  /* Compile body */
  block->compile();
  
  /* Create return value for void function without return statement inside its body */
  if(void_ret_type_without_ret_stmt)
    Builder.CreateRetVoid();

  llvm::verifyFunction(*f);
  return f;
}

llvmType * FuncDef::generateStackFrameStruct()
{
  /* Note:  we do not create LLVM instructions inside the function's body
   *        we just register the struct type that will be used to represent the stack frame of the function
  */

  /* This vector defines the types of the fields inside the struct
   * For every escaping parameter/variable we need a field that store a reference to the escaping variable
   * We maintain the same order that is used in local_defs vector.
   */
  std::vector<llvmType*> escapeTypes;

  /* Add static link to outer function */
  header->pushStaticLinkTypeForStackFrameStruct(&escapeTypes);

  /* Add types of the escaped parameters defined by this FuncDef to the escapeTypes vector */
  header->pushEscapeTypesForStackFrameStruct(&escapeTypes);

  /* Add types of the escaped variables defined by this FuncDef to the escapeTypes vector */
  for(LocalDef *i : *local_defs)
  {
    /* Check if this local def is a vardef */
    VarDef *var_def = dynamic_cast<VarDef*>(i);
    if(var_def) var_def->pushEscapeTypesForStackFrameStruct(&escapeTypes);
  }

  /* We use StructType::create instead of StructType::get to create a named struct
   * The unique name of the stack frame will be "sf_" + the mangled function name.
   * example: sf_f_14 
   */
  std::string stack_frame_name = getStackFrameName(header->getMangledName());
  return llvm::StructType::create(TheContext, escapeTypes, stack_frame_name);
}