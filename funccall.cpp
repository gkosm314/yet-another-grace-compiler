#include "funccall.hpp"

FuncCall::FuncCall(Id *f, std::vector<Expr *> *par) : funcName(f), parametersExprList(par) {}

FuncCall::~FuncCall() { 
  delete funcName; 
  for (Expr *e : *parametersExprList) 
    delete e;
  delete parametersExprList;
}

void FuncCall::printAST(std::ostream &out) const {
  bool first = true;
  out << "FuncCall(" << *funcName;
  if (!(parametersExprList->empty())) {
    out << "[";
    for (auto exprPtr : *parametersExprList) {
      if (!first)
        out << ",";
      first = false;
      out << *exprPtr;
    }
    out << "]";
  }
  out << ")";
}