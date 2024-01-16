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
  mangled_name = header->getMangledName();

  /* Perform semantic analysis for local definitions of the function */
  for (LocalDef *i : *local_defs)
  {
    i->sem();
    i->setOuterFunc(mangled_name);
  } 

  /* Perform semantic analysis for the statements of the function */
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
  llvm::Function *f = header->compile();

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
  /* This line must remain before the compilation of the local definition
   * because the definition of the stack frame structure is needed for the defintion
   * of the nested functions since their first parameter is a pointer to this structure
   */
  llvmType *stack_frame_type = generateStackFrameStruct();

  /* Allocate memory for local variables and compile local functions */
  for (LocalDef *i : *local_defs)
  {
    i->compile();
    /* We want to continue inserting code inside the current function */
    Builder.SetInsertPoint(BB);
  }

  /* Define LLVM type for the stack frame of this function and allocate memory for it */
  createStackFrame(stack_frame_type);
  /* Populate stack frame by assigning pointers to the escaped variables to its fields */
  populateStackFrame();

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

void FuncDef::setOuterFunc(std::string outer_func_mangled_name)
{
  outerFunc[mangled_name] = outer_func_mangled_name;
}

llvmType * FuncDef::generateStackFrameStruct()
{
  /* Note:  we do not create LLVM instructions inside the function's body
   *        we just register the struct type that will be used to represent the stack frame of the function
  */

  /* Add static link to outer function. This applies only to non-top-level functions */
  if(!isTopLevelFunc(mangled_name))
  {
    header->pushStaticLinkForStackFrameStruct(&escapeNames, &escapeTypes);
    escapeIsRef.push_back(true);
  }

  /* Add types of the escaped parameters defined by this FuncDef to the escapeTypes vector */
  header->pushFieldsForStackFrameStruct(&escapeNames, &escapeTypes, &escapeIsRef);

  /* Add types of the escaped variables defined by this FuncDef to the escapeTypes vector */
  for(LocalDef *i : *local_defs)
  {
    /* Check if this local def is a vardef */
    VarDef *var_def = dynamic_cast<VarDef*>(i);
    if(var_def)
    {
      var_def->pushFieldsForStackFrameStruct(&escapeNames, &escapeTypes);
      escapeIsRef.push_back(false);
    }
  }

  /* We use StructType::create instead of StructType::get to create a named struct
   * The unique name of the stack frame will be "sf_" + the mangled function name.
   * example: sf_f_14 
   */
  std::string stack_frame_type_name = getStackFrameStructName(mangled_name);
  return llvm::StructType::create(TheContext, escapeTypes, stack_frame_type_name);
}

void FuncDef::createStackFrame(llvmType *stack_frame_type)
{
  std::string stack_frame_name = getStackFrameName(mangled_name);
  /* Allocate memory for the stack frame struct */
  llvmAddr alloca = Builder.CreateAlloca(stack_frame_type, nullptr, stack_frame_name);  
  /* Add stack frame to the variable map */
  varMap[stack_frame_name] = alloca;  
}

void FuncDef::populateStackFrame()
{
  /* address of current stack frame */
  llvmAddr    stack_frame_addr = varMap[getStackFrameName(mangled_name)];
  /* type of current stack frame */
  llvmType   *stack_frame_type = llvm::StructType::getTypeByName(TheContext, getStackFrameStructName(mangled_name));

  /* Iterate over every field of our stack frame structure */
  unsigned int stack_frame_fields_cnt = escapeNames.size();
  for (unsigned int idx = 0; idx < stack_frame_fields_cnt; idx++)
  {
    /* get address of the stack frame's field we will populate in this iteration */
    llvmAddr stack_frame_field_addr = Builder.CreateStructGEP(stack_frame_type, stack_frame_addr, idx);
    llvmAddr escape_var_addr;
    
    /* get the address at which the escape var is stored */
    if(!escapeIsRef[idx]) escape_var_addr = varMap[escapeNames[idx]];
    else escape_var_addr = Builder.CreateLoad(escapeTypes[idx], varMap[escapeNames[idx]]);

    /* store the address of the escape var in the stack frame field */
    Builder.CreateStore(escape_var_addr ,stack_frame_field_addr);

    /* keep the index of the variable inside the stack frame so that you know where to look for it */
    stackframePos[escapeNames[idx]] = idx;
  }
}