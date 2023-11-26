#ifndef __BINOP_HPP__ 
#define __BINOP_HPP__ 

#include "expr.hpp"

class BinOp : public Expr 
{
  public:
    BinOp(Expr *l, char o, Expr *r);
    ~BinOp();
    void printAST(std::ostream &out) const override;
    void sem() override;

  private:
    Expr *left;
    char op;
    Expr *right;
};

#endif
