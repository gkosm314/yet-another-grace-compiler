#include <iostream>

#include "stmt.hpp"
#include "funccall.hpp"

/* For example f(); */
class FuncCallStmt : public Stmt
{
  public:
    FuncCallStmt::FuncCallStmt(FuncCall *fc);
    FuncCallStmt::~FuncCallStmt();
    void FuncCallStmt::printAST(std::ostream &out) const override;

  private:
    FuncCall* func;
};