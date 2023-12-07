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
  header->sem();
  for (LocalDef *i : *local_defs) i->sem();
  block->sem();

  /* The new scope is opened inside header->sem() */
  ret_types_stack.pop_back();
  closeScope();
}
