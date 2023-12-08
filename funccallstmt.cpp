#include "funccallstmt.hpp"

FuncCallStmt::FuncCallStmt(FuncCall *fc) : func(fc) {}

FuncCallStmt::~FuncCallStmt() { delete func; }

void FuncCallStmt::printAST(std::ostream &out) const {
  out << "FuncCallStmt(" << *func << ")";
}

void FuncCallStmt::sem()
{
  func->type_check(typeVoid);

  /* If the function has already returned we should not generate code */
  checkIfStmtIsAfterReturn();  
}