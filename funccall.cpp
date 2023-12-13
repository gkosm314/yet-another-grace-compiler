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

    if(f->entryType != ENTRY_FUNCTION) semError("Could not find function name.");

    SymbolEntry *current_argument = f->u.eFunction.firstArgument;

    for(Expr *e : *parameters_expr_list)
    {
      if(current_argument == NULL)
        semError("More parameters than expected in function call.");

      /* Check that the expression we pass has the same type as the typical parameter */
      e->type_check_param(current_argument->u.eParameter.type);

      if(current_argument->u.eParameter.mode == PASS_BY_REFERENCE && !e->isLvalue())
        semError("Parameter defined as pass-by-reference requires an lvalue.");

      current_argument = current_argument->u.eParameter.next;
    }

    if(current_argument != NULL)
      semError("Fewer parameters than expected in function call.");
    
    expr_type = f->u.eFunction.resultType;
}