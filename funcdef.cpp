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
  if(header->getParametersCount() != 0) yyerror("Program cannot take parameters");
  if(!equalType(header->getReturnType(), typeVoid)) yyerror("Program must be of type nothing");
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
    if(!return_stack.returnFound()) yyerror("Non-void function should have return statement.");
  }

  /* The new scope is opened inside header->sem() */
  return_stack.pop();
  closeScope();
}
