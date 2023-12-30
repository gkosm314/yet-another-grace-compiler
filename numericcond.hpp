#ifndef __NUMERICCOND_HPP__ 
#define __NUMERICCOND_HPP__ 

#include "condition.hpp"

class NumericCond : public Condition
{
  public:
    NumericCond(Expr *l, char o, Expr *r);
    ~NumericCond();
    void printAST(std::ostream &out) const override;
    void sem() override;
    llvm::Value* compile() override;

  private:
    Expr *left;
    char op;
    Expr *right;
};

#endif
