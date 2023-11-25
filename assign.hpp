#ifndef __ASSIGN_HPP__ 
#define __ASSIGN_HPP__ 

#include <iostream>

#include "stmt.hpp"
#include "abstractlvalue.hpp"

class Assign : public Stmt 
{
  public:
    Assign(AbstractLvalue *l, Expr *e);
    ~Assign();
    void printAST(std::ostream &out) const override;
    
  private:
    AbstractLvalue *lval;
    Expr *expr;
};

#endif
