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
  if(isForward)
    forwardFunction(f);

  openScope();
  ret_types_stack.push_back(ret_type);

  for (FParDef *p : *fpar_defs)
  {
    p->setFunction(f);
    p->sem();
  }
  endFunctionHeader(f, ret_type);
  
  /* The scope is closed by FuncDecl or FuncDef, because
     FuncDef needs to add local definitions in the same scope*/
}