#ifndef __UNARYOP_HPP__ 
#define __UNARYOP_HPP__ 

#include "expr.hpp"

class UnaryOp : public Expr 
{
  public:
    UnaryOp(char o, Expr *e);
    ~UnaryOp();
    void printAST(std::ostream &out) const override;
    void sem() override;

  private:
    Expr *expr;
    char op;
};


#endif
