#include "funcdecl.hpp"

FuncDecl::FuncDecl(Header *h) : header(h) {};

FuncDecl::~FuncDecl() { delete header; }

void FuncDecl::printAST(std::ostream &out) const {
  out << "FuncDecl(";
  out << *header;
  out << ")";
}

void FuncDecl::sem()
{  
  /* Notify the header that it should add the function to the symbol table
     as a forward declaration */
  header->setForward();

  /* Perform semantic analysis for forward declaration */
  header->sem();

  /* The new scope is opened inside header->sem() */
  return_stack.pop();
  closeScope();
}

llvm::Value* FuncDecl::compile()
{
  header->compile();
  return nullptr;
}

void FuncDecl::setOuterFunc(std::string outer_func_mangled_name)
{
  outerFunc[header->getMangledName()] = outer_func_mangled_name;
}