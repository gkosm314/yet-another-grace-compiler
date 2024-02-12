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
      AbstractLvalue *lval = dynamic_cast<AbstractLvalue*>(e);
      bool autocompletedRealParam = false;

      if(!lval) semError("Parameter defined as pass-by-reference requires an lvalue.");
      else autocompletedRealParam = lval->hasAutocompleteDimension();

      /* If either the typical or the real parameter have autocompleted dimension,
       * we have to perform a bitcast during the codegen of parameter passing to make the LLVM types match
       */
      if(current_argument->u.eParameter.type->autocompleteSize || autocompletedRealParam)
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
    llvmAddr stack_frame_addr = walkupStaticLinkChain(calleDeclDepth, callDepth);
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
        /* In case we want to pass a string to a fixed-length parameter (ref x:char[6])
         * we have to cast the i8* pointer returned from llvm::CreateGlobalStrPtr to [6 x i8]* */
        if(dynamic_cast<StrLit*>(e)) v = Builder.CreateBitCast(v, f->getFunctionType()->getParamType(current_param));
        break;
      case FUNC_CALL_ARG_PASS_BY_REF_WITH_AUTOCOMPLETE:
        v = ((AbstractLvalue *) e)->findLLVMAddr();
        /* Change the type LLVM assumes for this array in order for it to match the autocompleted type */
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