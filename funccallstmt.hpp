#ifndef __FUNCCALLSTMT_HPP__ 
#define __FUNCCALLSTMT_HPP__ 

#include "stmt.hpp"
#include "funccall.hpp"

/* For example f(); */
class FuncCallStmt : public Stmt
{
  public:
    FuncCallStmt(FuncCall *fc);
    ~FuncCallStmt();
    void printAST(std::ostream &out) const override;

  private:
    FuncCall* func;
};

#endif
