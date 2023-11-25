#include <iostream>

#include "expr.hpp"

class BinOp : public Expr 
{
  public:
    BinOp(Expr *l, char o, Expr *r);
    ~BinOp();
    void printAST(std::ostream &out) const override;

  private:
    Expr *left;
    char op;
    Expr *right;
};