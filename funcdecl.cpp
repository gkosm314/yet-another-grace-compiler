#include "funcdecl.hpp"

FuncDecl::FuncDecl(Header *h) : header(h) {};

FuncDecl::~FuncDecl() { delete header; }

void FuncDecl::printAST(std::ostream &out) const {
  out << "FuncDecl(";
  out << *header;
  out << ")";
}