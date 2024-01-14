#include "funccall.hpp"

FuncCall::FuncCall(Id *f, std::vector<Expr *> *par) : func_name(f), parameters_expr_list(par) {}

FuncCall::~FuncCall() { 
  delete func_name; 
  for (Expr *e : *parameters_expr_list) 
    delete e;
  delete parameters_expr_list;
}

void FuncCall::printAST(std::ostream &out) const {
  bool first = true;
  out << "FuncCall(" << *func_name;
  if (!(parameters_expr_list->empty())) {
    out << "[";
    for (auto exprPtr : *parameters_expr_list) {
      if (!first)
        out << ",";
      first = false;
      out << *exprPtr;
    }
    out << "]";
  }
  out << ")";
}

void FuncCall::sem()
{
  /* If the function name is not found, lookupEntry will throw an error */
  SymbolEntry *f = lookupEntry(func_name->getName(), LOOKUP_ALL_SCOPES, true);

  /* Store mangled name */
  mangled_name = mangle(func_name->getName(), f->scopeId);

  /* Keep nesting level of caller and calle to calculate which stack frame you should pass */
  callDepth = currentScope->nestingLevel;
  calleDeclDepth  = funcDepth[mangled_name];

  if(f->entryType != ENTRY_FUNCTION) semError("Could not find function name.");

  SymbolEntry *current_argument = f->u.eFunction.firstArgument;

  for(Expr *e : *parameters_expr_list)
  {
    if(current_argument == NULL)
      semError("More parameters than expected in function call.");

    /* Check that the expression we pass has the same type as the typical parameter */
    e->type_check_param(current_argument->u.eParameter.type);

    /* Track pass-by-ref parameters to generate address instead of value during codegen */
    if(current_argument->u.eParameter.mode == PASS_BY_REFERENCE)
    {
      /* Check that pass-by-reference parameter receives a lvalue as argument */
      if(!e->isLvalue()) semError("Parameter defined as pass-by-reference requires an lvalue.");

      if(current_argument->u.eParameter.type->autocompleteSize)
        parameters_pass_mode.push_back(FUNC_CALL_ARG_PASS_BY_REF_WITH_AUTOCOMPLETE);
      else
        parameters_pass_mode.push_back(FUNC_CALL_ARG_PASS_BY_REF);
    }
    else parameters_pass_mode.push_back(FUNC_CALL_ARG_PASS_BY_VALUE);

    current_argument = current_argument->u.eParameter.next;
  }

  if(current_argument != NULL)
    semError("Fewer parameters than expected in function call.");
  
  expr_type = f->u.eFunction.resultType;
}


llvm::Value* FuncCall::compile() {
  /*
    find mangled name from private class field
    find function ptr from llvm symbol table (with llvm built-in getFunction())
  */

  llvm::Function *f = TheModule->getFunction(mangled_name);

  std::vector<llvm::Value*> param_values;

  int current_param = 0;
  
  /* If the function we call is not a top-level function,
   * we have to pass a pointer to the appropriate stack frame as the first argument  */
  if(!isTopLevelFunc(mangled_name))
  {
    /* WARNING: This pass_mode will not be used, we insert it here so that the current_param index remains consistent */
    parameters_pass_mode.insert(parameters_pass_mode.begin(), FUNC_CALL_ARG_PASS_BY_REF);
    
    /* Walk up the static links chain to find the correct static link to pass as parameter */
    llvmAddr stack_frame_addr = getStackFramePtrToPass();
    param_values.push_back(stack_frame_addr);
    current_param++;
  }

  for (Expr *e : *parameters_expr_list)
  {
    llvm::Value *v = nullptr;

    /* If this parameter is pass-by-ref we pass its address, otherwise we pass its value */
    FUNC_CALL_ARG param_pass_mode = parameters_pass_mode[current_param];
    switch(param_pass_mode)
    {
      case FUNC_CALL_ARG_PASS_BY_VALUE:
        v = e->compile();
        break;
      case FUNC_CALL_ARG_PASS_BY_REF:
        v = ((AbstractLvalue *) e)->findLLVMAddr();
        break;
      case FUNC_CALL_ARG_PASS_BY_REF_WITH_AUTOCOMPLETE:
        v = ((AbstractLvalue *) e)->findLLVMAddr();
        /* TODO add comments*/
        v = Builder.CreateBitCast(v, f->getFunctionType()->getParamType(current_param));
        break;
    }

    current_param++;

    /* Push the argument */
    if(v != nullptr)
      param_values.push_back(v);
    else
      return nullptr;
  }

  return Builder.CreateCall(f, param_values);
}

llvmAddr FuncCall::getStackFramePtrToPass()
{
  /* Grab caller's name */
  llvm::Function *caller = Builder.GetInsertBlock()->getParent();

  /* The caller's first parameter is a pointer to a stack frame structure.
   * We have allocated memory for this stack frame structure. */
  std::string current_func_mangled_name = caller->getName().str();
  
  /* Note that we start walking up from the stack frame the caller created, 
     not from the stack frame that was passed to the caller as a parameter */
  
  /* address of current stack frame */
  llvmAddr    stack_frame_addr = varMap[getStackFrameName(current_func_mangled_name)];
  /* type of current stack frame */
  llvmType   *stack_frame_type = llvm::StructType::getTypeByName(TheContext, getStackFrameStructName(current_func_mangled_name));

  /* When invoking a function declared at a depth of k levels above the current call
   * (e.g., 1 for a recursive/sibling function because the call is within the body)
   * we walk up the frames chain upwards k times */
  unsigned int k = callDepth - calleDeclDepth;
  while (k > 0)
  {
    /* move to the outer function */
    current_func_mangled_name = outerFunc[current_func_mangled_name];
    /* type of next stack frame */
    llvmType *next_stack_frame_type = llvm::StructType::getTypeByName(TheContext, getStackFrameStructName(current_func_mangled_name));
    /* get address of next stack frame */
    stack_frame_addr = Builder.CreateLoad(next_stack_frame_type->getPointerTo(), Builder.CreateStructGEP(stack_frame_type, stack_frame_addr, 0));
    /* update the type of the current stack frame */
    stack_frame_type = next_stack_frame_type;

    k--;
  }

  return stack_frame_addr;
}