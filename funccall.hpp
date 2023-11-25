#ifndef __FUNCCALL_HPP__ 
#define __FUNCCALL_HPP__ 

#include <iostream>
#include <vector>

#include "expr.hpp"
#include "id.hpp"

/* In situations like a <- f(); the rhs has to implement eval() */ 
class FuncCall : public Expr 
{
  public:
    FuncCall(Id *f, std::vector<Expr *> *par);
    ~FuncCall();
    void printAST(std::ostream &out) const override;

  private:
    Id *funcName;
    std::vector<Expr *> *parametersExprList;
};

#endif
