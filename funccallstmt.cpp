#include "funccallstmt.hpp"

FuncCallStmt::FuncCallStmt(FuncCall *fc) : func(fc) {}

FuncCallStmt::~FuncCallStmt() { delete func; }

void FuncCallStmt::printAST(std::ostream &out) const {
  out << "FuncCallStmt(" << *func << ")";
}